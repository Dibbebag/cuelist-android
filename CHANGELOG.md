# Changelog – Cue List

Le modifiche sono elencate dalla più recente alla più vecchia.

## 11 novembre 2026 – telecomando
### Aggiunto
- **Telecomando da tablet o telefono** (solo Windows): il computer suona e il tablet, sulla stessa rete, mostra la vista show con GO, Indietro, Avanti, PANIC, lista delle cue con avanzamento e Stop per le cue in riproduzione. Si attiva in Impostazioni → *Telecomando*, protetto da un PIN, con porta e PIN modificabili.

## 11 novembre 2026
### Aggiunto
- **Aggiornamento automatico su Windows**: il tasto *Scarica e installa* ora scarica la nuova versione, la installa in silenzio e riapre il programma, senza passare dal browser. La versione portatile continua ad aprire il download.

## 10 novembre 2026 – nuovo logo
### Modificato
- **Nuovo logo** (G sbarrata, bianco e nero) al posto del precedente, in tutti i punti: icona dell'app Android (normale, rotonda e adattiva), schermata di avvio, icona e installer di Windows, intestazione dell'app e pagina Crediti. Nell'interfaccia il logo cambia colore con il tema chiaro o scuro.

## 10 novembre 2026
### Aggiunto
- **ASIO su Windows (sperimentale)**: nuovo driver *ASIO* nelle impostazioni audio. L'elenco dispositivi mostra i driver ASIO installati con i loro canali, e la modalità Dual mono o Base L/R + Click usa le uscite scelte. L'audio viene inviato alla scheda da un processo separato con una libreria PortAudio con ASIO, scaricata durante la build.

## 9 novembre 2026 – aggiornamento 5
### Aggiunto
- **Versione per Windows** (installer `CueList-Setup.exe` e versione portatile `CueList-Portable.exe`) con le stesse funzioni dell'app Android, compilata automaticamente su GitHub.
- **Scelta del driver audio su Windows**: WASAPI condiviso, WASAPI esclusivo (sperimentale) o MME / WaveOut. ASIO non è supportato. Pulsante per aprire il pannello audio di Windows.
- **Elenco dispositivi con il numero di canali** di ciascuna uscita e **Prima uscita** scelta da un elenco delle uscite disponibili (ricordata alla riapertura).
- Cartella `Documenti\CueList` su Windows con le sottocartelle Show, Brani e Autosalvataggi.
- Controllo aggiornamenti anche per Windows.

### Modificato
- Pagina Impostazioni senza emoji né simboli.

## 9 novembre 2026 – aggiornamento 4
### Aggiunto
- **Pan per ogni cue**, nella pagina edit sotto i cursori del volume: *Pan L* e *Pan R* in Dual mono, un solo *Pan* per la base nella modalità a 3 uscite. Si regola anche in tempo reale, compresa la pagina Impostazioni.

### Modificato
- **Pagina Impostazioni ridisegnata** con schede e menù a scomparsa, nell'ordine: Salva, Cartella dell'app, Uscita audio, Spettro delle cue, Volumi e pan in tempo reale, Crediti e, per ultima, Versione.
- All'apertura dell'app i brani in caricamento mostrano una clessidra ⏳ al posto della ✕ rossa, che compare solo se un file non si trova davvero.

### Rimosso
- Il pan sul master nel mixer in alto.

## 9 novembre 2026 – aggiornamento 3
### Aggiunto
- **Salto dentro la cue**: solo in modalità edit, la barra di avanzamento (e la forma d'onda, se attiva) è cliccabile e trascinabile per spostare la riproduzione avanti o indietro mentre la cue suona. In modalità Show non è cliccabile.

### Modificato
- **Riapertura dell'app**: riparte con l'ultima scaletta caricata, con la selezione nella stessa posizione. Oltre al salvataggio nel dispositivo, una copia dell'ultimo stato viene tenuta anche nella cartella `CueList` e usata se il primo manca.
- Riavviare una cue già in riproduzione ora la interrompe con una dissolvenza brevissima invece di tagliarla di colpo.

## 9 novembre 2026 – aggiornamento 2
### Aggiunto
- **Volumi in tempo reale**: i volumi delle cue (e Vol L / Vol R in Dual mono) cambiano subito mentre l'audio suona. Nuova sezione in ⚙ Impostazioni → *Volumi cue in tempo reale*, utilizzabile anche con la modalità Show attiva.
- **Autosalvataggio silenzioso** (nessun avviso), con scelta dell'intervallo in Impostazioni: disattivato, 5, 10, 15, 30 (predefinito) o 60 minuti. Si salva solo se lo show è cambiato e si tengono gli ultimi 10.
- **Cartella `CueList` creata dall'app** con le sottocartelle `Show`, `Brani` e `Autosalvataggi`, e nelle Impostazioni l'elenco degli autosalvataggi e degli show salvati da riaprire con un tocco.

### Modificato
- I brani importati ora vanno nella cartella `Brani` (i brani già importati vengono trovati comunque).
- *Salva show su file* salva anche una copia in `Show`, con data e ora nel nome.
- Il livello di una cue Fade ora è relativo al volume della cue.

### Corretto
- La build su GitHub non si ferma più quando il download di Gradle è lento: il tempo massimo è stato portato da 10 secondi a 2 minuti.

## 9 novembre 2026
### Aggiunto
- **Ricollegamento per cartella**: quando un brano non viene trovato, tocca la ✕ rossa e scegli la cartella dei brani. L'app cerca per nome (anche nelle sottocartelle) tutti i brani mancanti e ricostruisce da sola la cue list. Se il file non è nella cartella, ti chiede di sceglierlo a mano.
- **Cartelle ricordate**: le cartelle scelte restano autorizzate; aprendo uno show l'app le usa in automatico per trovare i brani.
- **Spettro per ogni cue** (forma d'onda con le parti fuori da inizio/fine attenuate e cursore durante la riproduzione). In ⚙ Impostazioni → *Spettro delle cue*: casella per attivarlo e scelta tra "solo in modalità edit" e "anche in modalità show" (non cliccabile).
- **File CHANGELOG** incluso nello zip a ogni aggiornamento.
- **README completo** con la descrizione di tutte le funzioni dell'app; viene aggiornato a ogni novità importante.

### Modificato
- La ✕ rossa ora apre la scelta della cartella invece del singolo file; il singolo file resta come ripiego.

## 8 novembre 2026
### Aggiunto
- **Salvataggio show su file** (finestra "Salva con nome": Download, Drive…) e apertura da file; rimossa la casella di testo.
- **Libreria audio interna**: i brani importati vengono copiati nell'app e ricollegati da soli all'apertura di uno show; ✕ rossa accanto al nome se un file manca (anche per il file Click).
- **Installazione degli aggiornamenti dall'app**: tasto *Scarica e installa* con avanzamento e installazione guidata da Android.
- **Logo G sbarrata** come icona dell'app, nell'intestazione e nella pagina About.
- **Modalità Dual mono** con volume L/R per cue, master separati per Base L e Base R, pan per canale.
- **Pagina About**: invito all'open source, link al codice e ringraziamenti. Aggiunta licenza MIT.
- **Aggiornamenti automatici (OTA)** dalle Release di GitHub, versione installata e tasto ⚙ Impostazioni.
- Firma fissa dell'APK, così le nuove versioni si installano sopra le vecchie.

### Modificato
- In modalità Show il nome della cue non è modificabile e si seleziona toccando in qualsiasi punto della riga.
- Tasti di aggiunta cue e tasti di modifica su due righe diverse.
- *Uscita audio e MIDI* e *Salva / apri show* spostati nelle Impostazioni.
- Cestino 🗑 per eliminare una cue (la ✕ rossa indica ora un file mancante).

## 8 novembre 2026 – prima versione
- Lista di cue con grande tasto **GO**, **PANIC**, avanti e indietro.
- Fade in e fade out, volume per cue, loop, inizio e fine, pre-wait, post-wait, Auto-continue e Auto-follow.
- Cue di tipo Fade, Stop e Gruppo; tasti rapidi; annulla e ripeti; riordino con trascinamento.
- Tre canali: Base L, Base R e Click, con meter e test canali.
- Trigger MIDI, modalità Show, salvataggio e apertura degli show.
