<p align="center">
  <img src="logo-vettoriale.png" alt="Logo Cue List" width="160">
</p>

# Cue List

Cue List è un'app per lanciare audio dal vivo con una **lista di cue**: un grande tasto **GO**, il tasto **PANIC**, fade, tempi di attesa, gruppi, uscite separate per Base e Click, spettro del brano e molto altro. È pensata per teatro, musica dal vivo, eventi e sonorizzazioni. Gira come app Android, come programma per Windows e anche in un normale browser (Chrome).

Questa app è software libero (licenza MIT): usala, studiala, modificala e condividila. Il codice è su https://github.com/Dibbebag/cuelist-android

---

## Scarica e installa

Basta un tocco, senza cercare nulla:

- **Android** (5.1 o successivo): scarica l'app da questo link: https://github.com/Dibbebag/cuelist-android/releases/latest/download/cuelist.apk
  Aprilo dal telefono e consenti l'installazione da origini sconosciute. Le versioni successive si installano dall'app, con il tasto *Scarica e installa*.
- **Windows** (10 o 11, 64 bit): scarica l'installer da questo link: https://github.com/Dibbebag/cuelist-android/releases/download/windows-latest/CueList-Setup.exe
  Windows può mostrare un avviso perché il programma non è firmato: scegli *Maggiori informazioni* e poi *Esegui comunque*. Dopo l'installazione il programma si aggiorna da solo.

I link puntano sempre all'ultima versione.

## 0. Schermata iniziale

All'apertura del programma compare la schermata iniziale, con tre scelte:
- **Nuovo show**: parte con una scaletta vuota. Se la scaletta precedente aveva delle cue, viene prima salvata negli Autosalvataggi (su Android e Windows). Nel browser non viene conservata.
- **Apri ultimo show**: riprende l'ultima scaletta com'era, con la selezione nello stesso punto. È disattivato se non c'è nessuno show precedente.
- **Apri show da archivio**: mostra gli show salvati nella cartella `Show` e ne apre uno con un tocco. Con **Scegli un file…** apri uno show salvato altrove.

## 1. Schermata principale

- **GO** (barra spaziatrice): lancia la cue selezionata e sposta la selezione alla successiva. Se la cue ha un Auto-continue o un Auto-follow, parte anche la catena di cue collegate.
- **◀ Indietro / Avanti ▶** (frecce ↑ ↓): spostano la selezione senza lanciare nulla.
- **PANIC** (tasto Esc): ferma tutto con un fade di 0,25 secondi e annulla anche le cue in attesa di partire.
- **Mixer in alto**: fader master e indicatori di livello (meter) delle uscite.
- **Valore predefinito**: un doppio clic (o doppio tocco) su un cursore lo riporta al valore predefinito: volume 1, pan centrale, oppure pan completo a sinistra e a destra per Pan L e Pan R.
- **Master in modalità Show**: in ⚙ Impostazioni → *Volumi e pan in tempo reale* puoi nascondere i master (Base, Click) in modalità Show, per evitare modifiche per sbaglio durante lo spettacolo.
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
