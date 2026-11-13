// asiotest - test nativo del driver ASIO: apre il driver e manda un tono diverso su ogni uscita.
// Uso: asiotest.exe            -> elenca i driver ASIO installati
//      asiotest.exe "<nome>"   -> apre il driver e suona su tutte le uscite (ESC per fermare)
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include "asiosys.h"
#include "asio.h"
#include "asiodrivers.h"

extern bool loadAsioDriver(char* name);
extern void removeCurrentDriver();
extern IASIO* theAsioDriver;

static ASIOBufferInfo infos[32];
static ASIOChannelInfo chInfo;
static ASIOCallbacks callbacks;
static long bufSize = 0, numOut = 0;
static ASIOSampleType sType = ASIOSTInt32LSB;
static double phase[32], freq[32];
static double sampleRate = 48000.0;
static volatile bool running = false;

static void fillBuffers(long idx) {
    for (long c = 0; c < numOut; c++) {
        void* b = infos[c].buffers[idx];
        double inc = 2.0 * M_PI * freq[c] / sampleRate;
        for (long s = 0; s < bufSize; s++) {
            double v = running ? 0.2 * sin(phase[c]) : 0.0;
            phase[c] += inc;
            if (phase[c] > 2.0 * M_PI) phase[c] -= 2.0 * M_PI;
            switch (sType) {
                case ASIOSTInt32LSB:   ((int*)b)[s] = (int)(v * 2147483647.0); break;
                case ASIOSTInt16LSB:   ((short*)b)[s] = (short)(v * 32767.0); break;
                case ASIOSTFloat32LSB: ((float*)b)[s] = (float)v; break;
                default: break;
            }
        }
    }
}

static void bufferSwitch(long idx, ASIOBool) {
    fillBuffers(idx);
    ASIOOutputReady();
}
static void sampleRateChanged(ASIOSampleRate) {}
static long asioMessage(long sel, long val, void*, double*) {
    switch (sel) {
        case kAsioSelectorSupported:
            return (val == kAsioEngineVersion || val == kAsioResetRequest || val == kAsioBufferSizeChange) ? 1 : 0;
        case kAsioEngineVersion: return 2;
        case kAsioResetRequest:  printf("Il driver chiede un reset\n"); return 1;
        case kAsioBufferSizeChange: return 0;
    }
    return 0;
}
static ASIOTime* bufferSwitchTimeInfo(ASIOTime*, long idx, ASIOBool d) {
    bufferSwitch(idx, d);
    return nullptr;
}

int main(int argc, char** argv) {
    CoInitialize(0);
    AsioDrivers ad;
    char* names[32];
    for (int i = 0; i < 32; i++) names[i] = new char[64];
    long n = ad.getDriverNames(names, 32);

    if (argc < 2) {
        printf("Driver ASIO installati (%ld):\n", n);
        for (long i = 0; i < n; i++) printf("  %s\n", names[i]);
        printf("\nUso: asiotest.exe \"<nome driver>\"\n");
        CoUninitialize();
        return 0;
    }

    if (!loadAsioDriver(argv[1])) {
        printf("ERRORE: impossibile caricare il driver \"%s\"\n", argv[1]);
        CoUninitialize();
        return 1;
    }

    ASIODriverInfo di;
    memset(&di, 0, sizeof(di));
    di.asioVersion = 2;
    di.sysRef = GetDesktopWindow();
    ASIOError err = ASIOInit(&di);
    if (err != ASE_OK) {
        printf("ERRORE ASIOInit: %ld\n", (long)err);
        removeCurrentDriver();
        CoUninitialize();
        return 1;
    }
    printf("Driver: %s (versione %ld)\n", di.name, di.driverVersion);

    long inCh = 0;
    ASIOGetChannels(&inCh, &numOut);
    printf("Uscite dichiarate dal driver: %ld\n", numOut);

    long mn, mx, pref, gran;
    ASIOGetBufferSize(&mn, &mx, &pref, &gran);
    bufSize = pref;
    printf("Buffer: %ld campioni\n", bufSize);

    if (ASIOCanSampleRate(48000.0) == ASE_OK) sampleRate = 48000.0;
    else sampleRate = 44100.0;
    ASIOSetSampleRate(sampleRate);
    printf("Frequenza: %.0f Hz\n", sampleRate);

    for (long c = 0; c < numOut && c < 32; c++) {
        infos[c].isInput = ASIOFalse;
        infos[c].channelNum = c;
        infos[c].buffers[0] = infos[c].buffers[1] = nullptr;
        freq[c] = 440.0 * (c + 1) / 2.0;   // ogni uscita ha un tono diverso
        phase[c] = 0.0;
    }

    callbacks.bufferSwitch = bufferSwitch;
    callbacks.sampleRateDidChange = sampleRateChanged;
    callbacks.asioMessage = asioMessage;
    callbacks.bufferSwitchTimeInfo = bufferSwitchTimeInfo;

    err = ASIOCreateBuffers(infos, numOut, bufSize, &callbacks);
    if (err != ASE_OK) {
        printf("ERRORE ASIOCreateBuffers: %ld\n", (long)err);
        ASIOExit();
        removeCurrentDriver();
        CoUninitialize();
        return 1;
    }

    memset(&chInfo, 0, sizeof(chInfo));
    chInfo.channel = 0;
    chInfo.isInput = ASIOFalse;
    ASIOGetChannelInfo(&chInfo);
    sType = chInfo.type;
    printf("Formato campioni: %d (%s)\n", (int)sType, chInfo.name);

    running = true;
    err = ASIOStart();
    if (err != ASE_OK) {
        printf("ERRORE ASIOStart: %ld\n", (long)err);
    } else {
        printf("Suono su %ld uscite (tono diverso per ogni uscita). ESC per fermare.\n", numOut);
        while (running) {
            if (_kbhit() && _getch() == 27) running = false;
            Sleep(50);
        }
        ASIOStop();
    }
    running = false;
    ASIODisposeBuffers();
    ASIOExit();
    removeCurrentDriver();
    CoUninitialize();
    printf("Fine.\n");
    return 0;
}
