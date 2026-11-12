<p align="center">
  <img src="1794401303013.jpg" alt="Logo Cue List" width="160">
</p>

# Cue List

Cue List è un'app per lanciare audio dal vivo con una **lista di cue**: un grande tasto **GO**, il tasto **PANIC**, fade, tempi di attesa, gruppi, uscite separate per Base e Click, spettro del brano e molto altro. È pensata per teatro, musica dal vivo, eventi e sonorizzazioni. Gira come app Android, come programma per Windows e anche in un normale browser (Chrome).

Questa app è software libero (licenza MIT): usala, studiala, modificala e condividila. Il codice è su https://github.com/Dibbebag/cuelist-android

---

## Scarica e installa

Tutte le versioni sono nella pagina **Releases** del repository: https://github.com/Dibbebag/cuelist-android/releases

- **Android** (5.1 o successivo): apri la release più recente chiamata *Build N* e scarica `cuelist.apk`. Aprilo dal telefono e consenti l'installazione da origini sconosciute. Le versioni successive si installano dall'app, con il tasto *Scarica e installa*.
- **Windows** (10 o 11, 64 bit): apri la release più recente chiamata *Windows build N* e scarica `CueList-Setup.exe` per installare il programma, oppure `CueList-Portable.exe` per usarlo senza installazione. Windows può mostrare un avviso perché il programma non è firmato: scegli *Maggiori informazioni* e poi *Esegui comunque*.
- Non scaricare i file dalla release *Windows - aggiornamento automatico*: serve solo all'aggiornamento automatico del programma.

## 1. Schermata principale

- **GO** (barra spaziatrice): lancia la cue selezionata e sposta la selezione alla successiva. Se la cue ha un Auto-continue o un Auto-follow, parte anche la catena di cue collegate.
- **◀ Indietro / Avanti ▶** (frecce ↑ ↓): spostano la selezione senza lanciare nulla.
- **PANIC** (tasto Esc): ferma tutto con un fade di 0,25 secondi e annulla anche le cue in attesa di partire.
- **Mixer in alto**: fader master e indicatori di livello (meter) delle uscite.
- **Lista delle cue**: la cue selezionata ha il bordo blu, quella in riproduzione diventa verde con una barra di avanzamento. Tocca in un punto qualsiasi di una cue per selezionarla.
- **Saltare dentro una cue** (solo in modalità edit): mentre una cue suona, tocca o **trascina** la barra verde di avanzamento in fondo alla cue (o la forma d'onda, se attiva) per spostare la riproduzione avanti o indietro. In modalità Show non è cliccabile.
- **Messaggi**: sotto il mixer compaiono avvisi, per esempio i brani non trovati.
- **⚙ Impostazioni** e **🔒 Show** in alto a destra.

## 2. Tipi di cue

Si aggiungono con i tasti della prima riga: **+ Audio**, **+ Fade**, **+ Stop**, **+ Gruppo**.

- **Audio**: riproduce un file. Si possono caricare più file insieme: ognuno diventa una cue. Formati supportati: quelli letti dal dispositivo (WAV, MP3, AAC, FLAC, OGG...).
- **Fade**: porta una cue in riproduzione a un nuovo livello (da 0 a 1,5 volte il suo volume) in un tempo scelto; con **Ferma** la cue si spegne alla fine del fade.
- **Stop**: ferma una cue (o tutte, scegliendo *Tutte*) con un fade.
- **Gruppo**: lancia insieme le N cue successive (numero a scelta).

## 3. Impostazioni di ogni cue

Valide per tutte le cue:
- **Nome** modificabile; numero, tipo e durata.
- **Pre-wait**: secondi di attesa prima che la cue parta.
- **Auto**: *Nessuno*, *Continue* (la cue successiva parte dopo il **Post-wait**) oppure *Follow* (la successiva parte quando questa finisce).
- **Tasto**: una lettera per lanciare la cue direttamente dalla tastiera, senza spostare la selezione.
- **■** ferma la cue con un fade (usa il suo fade out, o 1 secondo).
- **↑ ↓** e **trascinamento** (⋮⋮) per riordinare; **🗑** per eliminare (richiede una seconda conferma).

Solo per le cue Audio:
- **Fade in** e **Fade out** in secondi (il fade out si applica alla fine del brano).
- **Inizio** e **Fine**: tagliano il brano (Fine = 0 significa fino in fondo).
- **Loop** ripete la parte tra Inizio e Fine finché non la fermi.
- **Volume** e **Pan** per cue, sotto i cursori del volume (vedi sotto per il Dual mono).
- **Click**: associa un file separato per il canale Click.
- **Spettro** del brano (se attivato nelle impostazioni).

## 4. Audio e canali

Nelle impostazioni, in *Uscita audio e MIDI*, scegli la **Modalità**:

- **Dual mono (2 uscite)**: i due canali del file sono indipendenti. Un file stereo manda il canale 1 sul *Canale L* e il canale 2 sul *Canale R*; un file mono va su entrambi. Ogni canale ha **fader** e **meter** nel mixer, e ogni cue ha **Vol L** e **Vol R** con, sotto, **Pan L** e **Pan R** per posizionare ciascun canale nel campo stereo. Utile per esempio con base su un canale e click sull'altro.
- **Base L/R + Click (3 uscite)**: la base va su due uscite (L e R) e il Click su una terza. Il mixer ha un fader per la Base e uno per il Click, e ogni cue ha un solo **Vol** e un **Pan** per la base. Un file a 3 canali viene diviso da solo: canale 1 = L, canale 2 = R, canale 3 = Click.

Altre opzioni:
- **Dispositivo**: scelta dell'uscita audio (dove supportato), con il numero di canali di ciascuna uscita.
- **Prima uscita**: elenco delle uscite disponibili sul dispositivo scelto, per decidere da quale partire; utile con schede audio con molte uscite.
- **Test canali**: riproduce un tono su ogni uscita per controllare i collegamenti.
- Riga **Canali disponibili**: dice quante uscite vede il dispositivo.
- Se il dispositivo ha almeno 3 uscite e non hai scelto altro, parte da solo la modalità a 3 canali.

## 5. Spettro delle cue

In ⚙ Impostazioni → *Spettro delle cue*:
- una casella attiva la **forma d'onda** di ogni cue audio, con le parti fuori da Inizio/Fine attenuate e un cursore durante la riproduzione;
- una scelta decide se mostrarla **solo in modalità edit** oppure **anche in modalità show** (dove è visibile ma non cliccabile).

## 6. Modalità Show

Il tasto **🔒 Show** blocca le modifiche per evitare errori dal vivo: nascondono i tasti di aggiunta e modifica, i parametri delle cue e le impostazioni di uscita; il nome non si può cambiare e si seleziona la cue toccando in qualsiasi punto della riga. Restano disponibili GO, PANIC, avanti/indietro, ■ di ogni cue e, se manca un brano, la ✕ rossa per ricollegarlo. Premi di nuovo il tasto per tornare in modifica.

**Volumi in tempo reale, anche in Show**: durante le prove puoi aprire ⚙ Impostazioni → *Volumi cue in tempo reale* senza uscire dalla modalità Show. Le cue in riproduzione sono in cima, segnate come *in riproduzione*: muovendo i cursori il volume cambia subito mentre l'audio suona (un cursore per canale in Dual mono, uno solo nella modalità a 3 uscite). Anche i **pan** delle cue si regolano lì; il master di ciascun canale è nel mixer in alto, sempre disponibile. Anche i cursori di volume nella riga di ogni cue (in modalità edit) agiscono subito.

## 7. Salvare e aprire uno show

In ⚙ Impostazioni → *Salva / apri show*:
- **💾 Salva show su file** crea un file `.json` nel punto che scegli (Download, Drive...), che puoi spostare, copiare o condividere.
- **📂 Apri show da file** carica uno show salvato.
- Lo show corrente viene anche **salvato in automatico** nel dispositivo: chiudendo e riaprendo l'app riparte con **l'ultima scaletta** così com'era, con la selezione nella stessa posizione e i brani ricollegati da soli. Una copia di sicurezza dell'ultimo stato è anche nella cartella `CueList`.
- **Autosalvataggio**: in ⚙ Impostazioni → *Cartella dell'app, autosalvataggi e show* scegli ogni quanto salvare (5, 10, 15, 30 o 60 minuti, oppure disattivato; predefinito 30). Avviene in silenzio, senza avvisi, e solo se lo show è cambiato; si conservano gli ultimi 10.
- **Cartella dell'app**: l'app crea la cartella `CueList` con tre sottocartelle: `Show` (gli show che salvi), `Brani` (i brani importati) e `Autosalvataggi`. Nelle impostazioni vedi il percorso e gli elenchi di autosalvataggi e show salvati, da cui riapri uno show con un tocco. Ogni volta che usi **Salva show su file** una copia viene messa anche in `Show`.
- **↶ Annulla** e **↷ Ripeti** (fino a 100 passaggi) e **Nuovo** per svuotare la lista (con conferma).

## 8. Brani e ricollegamento automatico

- I brani importati con **+ Audio** vengono **copiati nella cartella `Brani` dell'app**, quindi restano disponibili anche se il file originale viene spostato.
- Aprendo uno show, l'app cerca da sola i brani: prima nel percorso salvato, poi per nome tra quelli già importati, poi nelle cartelle che hai già autorizzato.
- Mentre i brani si caricano compare una clessidra ⏳ accanto al nome: la ✕ rossa compare solo se un file non si trova davvero.
- Se un brano non si trova compare una **✕ rossa** accanto al nome. Toccala e **scegli la cartella dei brani**: l'app cerca per nome (anche nelle sottocartelle) tutti i brani mancanti e ricostruisce da sola la lista. Se il file non è in quella cartella, ti chiede di scegliere il brano a mano.
- Le cartelle scelte restano autorizzate per i prossimi show.
- Funziona allo stesso modo per i file Click.

## 9. Scorciatoie e MIDI

Da tastiera: **Spazio** = GO, **Esc** = PANIC, **↑ ↓** = selezione, **Ctrl+Z** = annulla, **Ctrl+Maiusc+Z** o **Ctrl+Y** = ripeti, e la lettera assegnata a ogni cue.

**MIDI** (nei browser che lo supportano; non è disponibile nell'app Android): in *Uscita audio e MIDI* premi **Attiva MIDI**. Le note predefinite sono 60 = GO, 61 = PANIC, 62 = Avanti, 63 = Indietro; toccando il tasto di ciascuna azione e premendo una nota sul controller puoi cambiarla.

## 10. Impostazioni, aggiornamenti e informazioni

La pagina ⚙ Impostazioni è organizzata in quest'ordine: **Salva**, **Cartella dell'app**, **Uscita audio**, **Spettro delle cue**, **Volumi e pan in tempo reale**, **Crediti** e, in fondo, **Versione** con la ricerca degli aggiornamenti.

- Nell'app Android, all'avvio e ogni 30 minuti, viene controllata la presenza di una nuova versione. Se c'è, compare una barra blu in alto con **Scarica e installa**; lo stesso tasto è in ⚙ Impostazioni, insieme a **Cerca aggiornamenti** e al **numero di versione**.
- L'app scarica l'aggiornamento e lo passa all'installazione di Android, che può chiedere una conferma. Al primo uso va consentito all'app di installare app sconosciute. Dopo l'installazione Android chiude l'app: riaprila.
- La pagina **Info e crediti** contiene il logo, l'invito all'open source, il link al codice e i ringraziamenti.

## 11. Versione per Windows

Cue List esiste anche come programma per Windows, con le stesse funzioni dell'app Android.

- **Dove scaricarla**: nella pagina Releases del repository, nelle versioni con nome *Windows build N*. Il file `CueList-Setup.exe` è l'installer; `CueList-Portable.exe` parte senza installazione. Poiché il programma non è firmato, Windows può mostrare l'avviso SmartScreen: scegli *Maggiori informazioni* e poi *Esegui comunque*.
- **Cartella**: viene creata `Documenti\CueList` con le sottocartelle `Show`, `Brani` e `Autosalvataggi`. Salva e apri show usano le normali finestre di Windows.
- **Driver audio**: in ⚙ Impostazioni → *Uscita audio* scegli il **Driver audio**: *WASAPI condiviso* (consigliato), *WASAPI esclusivo* (sperimentale, bassa latenza), *MME / WaveOut* oppure *ASIO* (sperimentale). Cambiando driver il programma si riavvia. Sotto scegli il **Dispositivo**, con il numero di canali di ciascuna uscita, e la **Prima uscita** tra quelle disponibili. Con ASIO l'elenco mostra i dispositivi ASIO installati (per esempio il driver della scheda Behringer) con i loro canali.
- **ASIO (sperimentale)**: serve il driver ASIO della scheda audio, installato in Windows. Il programma scrive l'audio sulla scheda attraverso una libreria PortAudio con supporto ASIO, in un processo separato, così le uscite multicanale sono tutte disponibili. L'audio passa da un buffer: aspettati una latenza dalla pressione di GO al suono di circa 100 millisecondi o più; se il driver è già in uso da un altro programma può non aprirsi. Se la libreria ASIO manca, la voce ASIO non compare.
- **Senza ASIO**: per usare più di due uscite con una scheda multicanale scegli il suo dispositivo e imposta il numero di canali nel pannello audio di Windows (formato predefinito del dispositivo): il tasto *Apri il pannello audio di Windows* lo apre.
- **Aggiornamenti automatici**: il programma controlla le nuove versioni all'avvio e ogni 30 minuti. Quando ce n'è una compare una barra in alto con **Scarica e installa**: il programma scarica l'aggiornamento, lo installa in silenzio e si riapre da solo. Lo stesso tasto è in ⚙ Impostazioni → *Versione*. Funziona con la versione installata con `CueList-Setup.exe`; la versione portatile non può aggiornarsi da sola e apre invece il download.
- **MIDI** funziona come nel browser.

## 12. Telecomando da tablet (Windows)

Il computer fa suonare lo show e il tablet, o un telefono, funziona da semplice telecomando con la vista show.

- **Attivazione**: sul computer apri ⚙ Impostazioni → *Telecomando (tablet o telefono)* e attiva **Telecomando attivo**. Alla prima attivazione Windows può chiedere di consentire l'accesso alla rete: scegli le reti private. Puoi cambiare la **Porta** (predefinita 8080).
- **Collegamento**: sul tablet, collegato alla stessa rete Wi-Fi del computer, apri nel browser l'indirizzo mostrato sotto *Da aprire nel browser del tablet* (per esempio `http://192.168.1.20:8080`) e inserisci il **PIN** mostrato sul computer. Con **Nuovo PIN** lo cambi.
- **Cosa mostra e cosa fa**: la lista delle cue con quella selezionata, quelle in riproduzione e la loro barra di avanzamento; i tasti grandi **GO**, **Indietro**, **Avanti** e **PANIC**; toccando una cue la selezioni; sulle cue audio in riproduzione compare **Stop**. Nel computer vedi quanti dispositivi sono collegati.
- **Sicurezza**: il telecomando è spento finché non lo attivi e richiede il PIN. Funziona solo sulla rete locale: chiunque sia sulla stessa rete e conosca il PIN potrebbe comandare lo show, quindi usalo su reti di cui ti fidi.
- Il telecomando funziona solo con la versione per Windows, che deve restare acceso con lo show aperto.

## 13. Limiti noti

- Su telefoni e tablet Android l'audio passa dal browser integrato (WebView), che di solito offre solo 2 uscite: con una scheda audio multicanale il numero di uscite visibili dipende da Android. Controlla la riga *Canali disponibili*.
- MIDI e scelta del dispositivo di uscita possono non essere disponibili nell'app Android.
- Le copie dei brani occupano spazio nel dispositivo e vengono cancellate se disinstalli l'app.
- Aprendo lo show su un altro dispositivo i brani vanno ricollegati una volta con la ✕ rossa.
- Saltando dentro una cue, i tempi di Auto-follow già programmati non si spostano.
- Inizio, Fine, fade e loop di una cue valgono dal lancio successivo; volumi e pan delle cue si cambiano invece in tempo reale.
- Su Android 11 e successivi alcune app per i file non mostrano la cartella `Android/data` in cui si trova `CueList`: per portare uno show fuori dal telefono usa **Salva show su file**.

---

## Per sviluppatori

### Configurazione (una volta sola)
1. Repository **pubblico** su GitHub con questo zip nella radice.
2. Settings → Secrets and variables → Actions: crea il secret `KEYSTORE_PASSWORD` con una password lunga e casuale.
3. Crea `.github/workflows/build.yml` con il workflow fornito (non cambiare mai il nome del file).

### Aggiornare l'app
Carica un nuovo zip: parte la build, viene firmata con la stessa chiave e pubblicata come Release. L'app installata la propone da sola. Non perdere né cambiare `KEYSTORE_PASSWORD` e `release.keystore`: senza la stessa chiave Android rifiuta l'aggiornamento.

### Struttura
- `www/index.html`: tutta l'interfaccia e la logica audio (HTML, CSS e JavaScript, Web Audio API).
- `windows/`: programma per Windows (Electron): `main.js`, `preload.js`, `asio-proc.js` (uscita ASIO), `controller.html` (pagina del telecomando) e `package.win.json`; i file dell'interfaccia vengono presi da `www/`.
- `.github/workflows/build-windows.yml`: compila installer e versione portatile per Windows.
- `android-src/`: plugin Android (`CueUpdater.java`): installazione degli aggiornamenti, selezione dei brani e delle cartelle, salvataggio dei file, cartella `CueList` e autosalvataggi.
- `android-res/` e `resources/`: icona, schermata di avvio e logo dell'app (originale in `resources/logo-originale.png`).
- `scripts/after-sync.sh`: copia icone e plugin nel progetto Android dopo `cap sync` (hook in `package.json`).
- `CHANGELOG.md`: elenco delle modifiche a ogni aggiornamento.
- `LICENSE`: licenza MIT.

---

*Questo README descrive tutte le funzioni dell'app e viene aggiornato a ogni novità importante. Le modifiche, versione per versione, sono nel file `CHANGELOG.md`.*
