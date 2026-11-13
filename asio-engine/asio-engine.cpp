// asio-engine - motore audio nativo ASIO (passo 1).
// Riproduce file WAV su uscite scelte liberamente, con volume, dissolvenza e PANIC.
// Comandi da tastiera, uno per riga:
//   load <id> <file.wav>            carica un WAV alla frequenza del driver (PCM 16/24/32 o float)
//   play <id> <inizio_s> <u1,u2,..> suona la voce id sulle uscite indicate (1 = prima uscita)
//   vol <id> <0..1.5>               cambia il volume di una voce
//   stop <id> <fade_s>              ferma una voce con dissolvenza
//   panic                           ferma tutto (dissolvenza 0,25 s)
//   outs                            mostra quante uscite ha il driver
//   quit                            chiude il motore
#define NOMINMAX
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <mutex>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "asiosys.h"
#include "asio.h"
#include "asiodrivers.h"

extern bool loadAsioDriver(char* name);

struct Clip { std::vector<float> d; int ch = 0; long frames = 0; unsigned long sr = 0; };
struct Voice {
    int id; int clip; long long pos; float gain; float fade; float fadeStep;
    bool stopping; bool done; std::vector<int> outs;
};

static std::mutex mtx;
static std::map<int, Clip> clips;
static std::vector<Voice> voices;
static std::vector<float> mix;           // [uscita][campione], in virgola mobile
static ASIOBufferInfo infos[32];
static ASIOCallbacks callbacks;
static long bufSize = 0, numOut = 0;
static ASIOSampleType sType = ASIOSTInt32LSB;
static double sampleRate = 48000.0;

// Chiamato dal driver: non aspetta mai il lavoro del thread comandi (try_lock)
static void render(long idx) {
    std::unique_lock<std::mutex> lk(mtx, std::try_to_lock);
    std::fill(mix.begin(), mix.end(), 0.0f);
    if (lk.owns_lock()) {
        for (auto& v : voices) {
            if (v.done) continue;
            auto it = clips.find(v.clip);
            if (it == clips.end()) { v.done = true; continue; }
            const Clip& c = it->second;
            int nch = std::min(c.ch, (int)v.outs.size());
            for (long f = 0; f < bufSize; f++) {
                if (v.pos >= c.frames) { v.done = true; break; }
                float g = v.gain * v.fade;
                long long base = v.pos * c.ch;
                for (int k = 0; k < nch; k++)
                    mix[(size_t)v.outs[k] * bufSize + f] += c.d[(size_t)(base + k)] * g;
                v.pos++;
                if (v.stopping) {
                    v.fade -= v.fadeStep;
                    if (v.fade <= 0.0f) { v.fade = 0.0f; v.done = true; break; }
                }
            }
        }
        voices.erase(std::remove_if(voices.begin(), voices.end(),
                     [](const Voice& v) { return v.done; }), voices.end());
    }
    for (long c = 0; c < numOut; c++) {
        void* b = infos[c].buffers[idx];
        const float* m = &mix[(size_t)c * bufSize];
        for (long s = 0; s < bufSize; s++) {
            float v = m[s];
            if (v > 1.0f) v = 1.0f;
            if (v < -1.0f) v = -1.0f;
            switch (sType) {
                case ASIOSTInt32LSB:   ((int*)b)[s] = (int)(v * 2147483647.0); break;
                case ASIOSTInt16LSB:   ((short*)b)[s] = (short)(v * 32767.0); break;
                case ASIOSTFloat32LSB: ((float*)b)[s] = v; break;
                default: break;
            }
        }
    }
}

static void bufferSwitch(long idx, ASIOBool) { render(idx); ASIOOutputReady(); }
static void sampleRateChanged(ASIOSampleRate) {}
static long asioMessage(long sel, long val, void*, double*) {
    switch (sel) {
        case kAsioSelectorSupported:
            return (val == kAsioEngineVersion || val == kAsioResetRequest || val == kAsioBufferSizeChange) ? 1 : 0;
        case kAsioEngineVersion: return 2;
        case kAsioResetRequest: return 1;
    }
    return 0;
}
static ASIOTime* bufferSwitchTimeInfo(ASIOTime*, long idx, ASIOBool d) { bufferSwitch(idx, d); return nullptr; }

// Lettura WAV: restituisce false con un messaggio se il formato non è supportato
static bool loadWav(const char* path, Clip& c, std::string& err) {
    FILE* f = fopen(path, "rb");
    if (!f) { err = "file non trovato"; return false; }
    std::vector<unsigned char> b;
    unsigned char tmp[65536];
    size_t n;
    while ((n = fread(tmp, 1, sizeof(tmp), f)) > 0) b.insert(b.end(), tmp, tmp + n);
    fclose(f);
    if (b.size() < 12 || memcmp(&b[0], "RIFF", 4) != 0 || memcmp(&b[8], "WAVE", 4) != 0) { err = "non è un file WAV"; return false; }
    auto u16 = [&](size_t o) -> unsigned { return (unsigned)b[o] | ((unsigned)b[o + 1] << 8); };
    auto u32 = [&](size_t o) -> unsigned long {
        return (unsigned long)b[o] | ((unsigned long)b[o + 1] << 8) | ((unsigned long)b[o + 2] << 16) | ((unsigned long)b[o + 3] << 24);
    };
    unsigned fmt = 0, ch = 0, bits = 0;
    unsigned long sr = 0;
    size_t dataOff = 0, dataLen = 0;
    bool gotFmt = false, gotData = false;
    size_t p = 12;
    while (p + 8 <= b.size()) {
        unsigned long sz = u32(p + 4);
        size_t body = p + 8;
        if (memcmp(&b[p], "fmt ", 4) == 0 && body + 16 <= b.size()) {
            fmt = u16(body); ch = u16(body + 2); sr = u32(body + 4); bits = u16(body + 14);
            if (fmt == 0xFFFE && sz >= 26 && body + 26 <= b.size()) fmt = u16(body + 24);
            gotFmt = true;
        } else if (memcmp(&b[p], "data", 4) == 0) {
            dataOff = body;
            dataLen = std::min<size_t>((size_t)sz, b.size() - body);
            gotData = true;
        }
        if (gotFmt && gotData) break;
        p = body + sz + (sz & 1);
    }
    if (!gotFmt || !gotData) { err = "WAV senza fmt o data"; return false; }
    bool ok = (fmt == 1 && (bits == 16 || bits == 24 || bits == 32)) || (fmt == 3 && bits == 32);
    if (!ok) { err = "formato non supportato: usa PCM 16/24/32 bit o float 32 bit"; return false; }
    if (ch < 1 || ch > 32) { err = "numero di canali non valido"; return false; }
    size_t bps = bits / 8;
    long frames = (long)(dataLen / (bps * ch));
    c.ch = (int)ch; c.frames = frames; c.sr = sr;
    c.d.assign((size_t)frames * ch, 0.0f);
    for (size_t i = 0; i < c.d.size(); i++) {
        size_t o = dataOff + i * bps;
        float v;
        if (fmt == 3) {
            unsigned int u = (unsigned int)u32(o);
            memcpy(&v, &u, 4);
        } else if (bits == 16) {
            v = (float)(short)u16(o) / 32768.0f;
        } else if (bits == 24) {
            int s = (int)(((unsigned)b[o] << 8) | ((unsigned)b[o + 1] << 16) | ((unsigned)b[o + 2] << 24));
            v = (float)(s >> 8) / 8388608.0f;
        } else {
            v = (float)((int)u32(o)) / 2147483648.0f;
        }
        c.d[i] = v;
    }
    return true;
}

static std::vector<int> parseOuts(const std::string& s, bool& ok) {
    std::vector<int> r;
    std::stringstream ss(s);
    std::string tok;
    ok = true;
    while (std::getline(ss, tok, ',')) {
        int u = atoi(tok.c_str());
        if (u < 1 || u > numOut) { ok = false; return r; }
        r.push_back(u - 1);
    }
    return r;
}

int main(int argc, char** argv) {
    CoInitialize(0);
    if (argc < 2) {
        printf("Uso: asio-engine.exe \"<nome driver>\"\n");
        CoUninitialize();
        return 1;
    }
    if (!loadAsioDriver(argv[1])) { printf("ERR impossibile caricare il driver\n"); CoUninitialize(); return 1; }

    AsioDrivers ad;
    ASIODriverInfo di;
    memset(&di, 0, sizeof(di));
    di.asioVersion = 2;
    di.sysRef = GetDesktopWindow();
    if (ASIOInit(&di) != ASE_OK) { printf("ERR ASIOInit\n"); ad.removeCurrentDriver(); CoUninitialize(); return 1; }

    long inCh = 0;
    ASIOGetChannels(&inCh, &numOut);
    long mn, mx, pref, gran;
    ASIOGetBufferSize(&mn, &mx, &pref, &gran);
    bufSize = pref;
    sampleRate = (ASIOCanSampleRate(48000.0) == ASE_OK) ? 48000.0 : 44100.0;
    ASIOSetSampleRate(sampleRate);

    for (long c = 0; c < numOut && c < 32; c++) {
        infos[c].isInput = ASIOFalse;
        infos[c].channelNum = c;
        infos[c].buffers[0] = infos[c].buffers[1] = nullptr;
    }
    callbacks.bufferSwitch = bufferSwitch;
    callbacks.sampleRateDidChange = sampleRateChanged;
    callbacks.asioMessage = asioMessage;
    callbacks.bufferSwitchTimeInfo = bufferSwitchTimeInfo;
    if (ASIOCreateBuffers(infos, numOut, bufSize, &callbacks) != ASE_OK) {
        printf("ERR ASIOCreateBuffers\n");
        ASIOExit(); ad.removeCurrentDriver(); CoUninitialize();
        return 1;
    }
    ASIOChannelInfo ci;
    memset(&ci, 0, sizeof(ci));
    ci.channel = 0; ci.isInput = ASIOFalse;
    ASIOGetChannelInfo(&ci);
    sType = ci.type;
    mix.assign((size_t)numOut * bufSize, 0.0f);

    if (ASIOStart() != ASE_OK) { printf("ERR ASIOStart\n"); ASIOExit(); ad.removeCurrentDriver(); CoUninitialize(); return 1; }
    printf("OK pronto: %ld uscite, %ld campioni, %.0f Hz\n", numOut, bufSize, sampleRate);
    fflush(stdout);

    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream in(line);
        std::string cmd;
        in >> cmd;
        if (cmd.empty()) continue;
        if (cmd == "quit") break;
        if (cmd == "outs") {
            printf("OK uscite: %ld\n", numOut);
        } else if (cmd == "load") {
            int id; std::string path;
            in >> id; std::getline(in >> std::ws, path);
            Clip c; std::string err;
            if (!loadWav(path.c_str(), c, err)) { printf("ERR %s\n", err.c_str()); }
            else if ((double)c.sr != sampleRate) {
                printf("ERR il file e a %lu Hz, il driver a %.0f Hz: esporta il file a %.0f Hz\n", c.sr, sampleRate, sampleRate);
            } else {
                std::lock_guard<std::mutex> lk(mtx);
                clips[id] = std::move(c);
                printf("OK caricato %d\n", id);
            }
        } else if (cmd == "play") {
            int id; double start; std::string list;
            in >> id >> start >> list;
            bool ok;
            std::vector<int> outs = parseOuts(list, ok);
            if (!ok || outs.empty()) { printf("ERR uscite non valide (usa numeri da 1 a %ld, separati da virgole)\n", numOut); }
            else {
                std::lock_guard<std::mutex> lk(mtx);
                if (clips.find(id) == clips.end()) { printf("ERR voce %d non caricata\n", id); }
                else {
                    voices.erase(std::remove_if(voices.begin(), voices.end(),
                                 [id](const Voice& v) { return v.id == id; }), voices.end());
                    Voice v;
                    v.id = id; v.clip = id; v.pos = (long long)(start * sampleRate);
                    v.gain = 1.0f; v.fade = 1.0f; v.fadeStep = 0.0f;
                    v.stopping = false; v.done = false; v.outs = outs;
                    voices.push_back(v);
                    printf("OK suona %d su uscite", id);
                    for (int o : outs) printf(" %d", o + 1);
                    printf("\n");
                }
            }
        } else if (cmd == "vol") {
            int id; float g;
            in >> id >> g;
            std::lock_guard<std::mutex> lk(mtx);
            for (auto& v : voices) if (v.id == id) v.gain = std::max(0.0f, std::min(1.5f, g));
            printf("OK\n");
        } else if (cmd == "stop") {
            int id; double sec = 0.0;
            in >> id >> sec;
            if (sec < 0.01) sec = 0.01;
            std::lock_guard<std::mutex> lk(mtx);
            for (auto& v : voices) if (v.id == id && !v.stopping) {
                v.stopping = true; v.fadeStep = (float)(1.0 / (sec * sampleRate));
            }
            printf("OK\n");
        } else if (cmd == "panic") {
            std::lock_guard<std::mutex> lk(mtx);
            for (auto& v : voices) if (!v.stopping) {
                v.stopping = true; v.fadeStep = (float)(1.0 / (0.25 * sampleRate));
            }
            printf("OK panic\n");
        } else {
            printf("ERR comando sconosciuto: %s\n", cmd.c_str());
        }
        fflush(stdout);
    }

    ASIOStop();
    ASIODisposeBuffers();
    ASIOExit();
    ad.removeCurrentDriver();
    CoUninitialize();
    return 0;
}
