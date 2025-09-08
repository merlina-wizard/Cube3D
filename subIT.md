# cub3D
## Il mio primo RayCaster con miniLibX

**Riassunto:** Questo progetto è ispirato al celebre gioco Wolfenstein 3D, considerato il primo FPS mai creato. Ti permetterà di esplorare il ray-casting. Il tuo obiettivo sarà creare una vista dinamica all'interno di un labirinto, dove dovrai trovare la tua strada.

**Versione:** 11.0

---

## Indice

I. **Premessa** - 2  
II. **Obiettivi** - 4  
III. **Istruzioni Comuni** - 5  
IV. **Istruzioni AI** - 7  
V. **Parte Obbligatoria - cub3D** - 9  
VI. **Parte Bonus** - 14  
VII. **Esempi** - 15  
VIII. **Consegna e peer-evaluation** - 18  

---

## Capitolo I - Premessa

Sviluppato da Id Software, guidato dai rinomati John Carmack e John Romero, e pubblicato nel 1992 da Apogee Software, Wolfenstein 3D è il primo vero "First Person Shooter" nella storia dei videogiochi.

Wolfenstein 3D è l'antenato di giochi come Doom (Id Software, 1993), Doom II (Id Software, 1994), Duke Nukem 3D (3D Realm, 1996) e Quake (Id Software, 1996), che sono pietre miliari eterne nel mondo dei videogiochi.

Ora, è il tuo turno di rivivere la Storia...

> ⚠️ **Nota:** Il gioco Wolfenstein 3D si svolge originariamente nella Germania nazista, il che potrebbe essere potenzialmente disturbante. Immagini e storia di questo gioco sono portate solo per ragioni tecniche e di cultura pop/geek, poiché il gioco era considerato un capolavoro per entrambe.

---

## Capitolo II - Obiettivi

Gli obiettivi di questo progetto sono simili a tutti gli obiettivi del primo anno: rigore, uso del C, algoritmi di base, ricerca di informazioni, ecc.

Come progetto di design grafico, cub3D ti permetterà di migliorare le tue competenze in queste aree: finestre, colori, eventi, riempimento di forme, ecc.

In conclusione, cub3D è un campo di gioco notevole per esplorare le applicazioni pratiche e ludiche della matematica senza dover comprendere le specifiche.

Con l'aiuto di numerosi documenti disponibili su internet, userai la matematica come strumento per creare algoritmi eleganti ed efficienti.

Se ti va, puoi testare il gioco originale prima di iniziare questo progetto:
http://users.atw.hu/wolf3d/

---

## Capitolo III - Istruzioni Comuni

- Il tuo progetto deve essere scritto in C.

- Il tuo progetto deve essere scritto in conformità con la Norma. Se hai file/funzioni bonus, sono inclusi nel controllo della norma e riceverai 0 se c'è un errore di norma.

- Le tue funzioni non devono terminare inaspettatamente (segmentation fault, bus error, double free, ecc.) tranne che per comportamenti indefiniti. Se ciò accade, il tuo progetto sarà considerato non funzionale e riceverà 0 durante la valutazione.

- Tutta la memoria allocata nell'heap deve essere liberata correttamente quando necessario. Le perdite di memoria non saranno tollerate.

- Se il subject lo richiede, devi consegnare un Makefile che compili i tuoi file sorgente nell'output richiesto con i flag -Wall, -Wextra e -Werror, usando cc. Inoltre, il tuo Makefile non deve eseguire ricompilazioni non necessarie.

- Il tuo Makefile deve contenere almeno le regole $(NAME), all, clean, fclean e re.

- Per consegnare i bonus del tuo progetto, devi includere una regola bonus nel tuo Makefile, che aggiungerà tutti i vari header, librerie o funzioni che non sono ammessi nella parte principale del progetto. I bonus devono essere posizionati in file _bonus.{c/h}, a meno che il subject non specifichi diversamente. La valutazione delle parti obbligatorie e bonus è condotta separatamente.

- Se il tuo progetto ti permette di usare la tua libft, devi copiare i suoi sorgenti e il suo Makefile associato in una cartella libft. Il Makefile del tuo progetto deve compilare la libreria usando il suo Makefile, poi compilare il progetto.

- Ti incoraggiamo a creare programmi di test per il tuo progetto, anche se questo lavoro non deve essere consegnato e non sarà valutato. Ti darà l'opportunità di testare facilmente il tuo lavoro e il lavoro dei tuoi pari. Troverai questi test particolarmente utili durante la tua difesa.

- Consegna il tuo lavoro nel repository Git assegnato. Solo il lavoro nel repository Git sarà valutato.

---

## Capitolo IV - Istruzioni AI

### Contesto
Durante il tuo percorso di apprendimento, l'AI può assistere con molti compiti differenti. Prenditi il tempo per esplorare le varie capacità degli strumenti AI e come possono supportare il tuo lavoro. Tuttavia, avvicinati sempre con cautela e valuta criticamente i risultati.

### Messaggio principale
☛ Usa l'AI per ridurre compiti ripetitivi o noiosi.  
☛ Sviluppa competenze di prompting - sia di coding che non - che beneficeranno la tua futura carriera.  
☛ Impara come funzionano i sistemi AI per anticipare ed evitare rischi comuni, bias e problemi etici.  
☛ Continua a costruire competenze sia tecniche che trasversali lavorando con i tuoi pari.  
☛ Usa solo contenuti generati dall'AI che comprendi pienamente e di cui puoi assumerti la responsabilità.

### Regole per gli studenti:
- Dovresti prenderti il tempo per esplorare gli strumenti AI e capire come funzionano, così puoi usarli eticamente e ridurre potenziali bias.
- Dovresti riflettere sul tuo problema prima di fare prompt - questo ti aiuta a scrivere prompt più chiari, dettagliati e rilevanti usando un vocabolario accurato.
- Dovresti sviluppare l'abitudine di controllare, rivedere, mettere in discussione e testare sistematicamente qualsiasi cosa generata dall'AI.
- Dovresti sempre cercare revisioni tra pari - non affidarti solo alla tua validazione.

### Esempi di buone e cattive pratiche:

✓ **Buona pratica:** Chiedo all'AI: "Come testo una funzione di ordinamento?" Mi dà alcune idee. Le provo e rivedo i risultati con un pari. Affiniamo l'approccio insieme.

✗ **Cattiva pratica:** Chiedo all'AI di scrivere un'intera funzione, la copio-incollo nel mio progetto. Durante la peer-evaluation, non posso spiegare cosa fa o perché. Perdo credibilità - e fallisco il progetto.

---

## Capitolo V - Parte Obbligatoria - cub3D

| **Nome programma** | cub3D |
|-------------------|-------|
| **File da consegnare** | Tutti i tuoi file |
| **Makefile** | all, clean, fclean, re, bonus |
| **Argomenti** | una mappa in formato *.cub |
| **Funzioni esterne** | • open, close, read, write, printf, malloc, free, perror, strerror, exit, gettimeofday<br>• Tutte le funzioni della libreria matematica (-lm man man 3 math)<br>• gettimeofday()<br>• Tutte le funzioni della libreria MinilibX |
| **Libft autorizzata** | Sì |
| **Descrizione** | Devi creare una rappresentazione grafica 3D "realistica" dell'interno di un labirinto da una prospettiva in prima persona. Devi creare questa rappresentazione usando i principi del ray-casting menzionati in precedenza. |

### I vincoli sono i seguenti:

- Devi usare la miniLibX. O la versione disponibile sul sistema operativo, o dai suoi sorgenti.

- La gestione della tua finestra deve rimanere fluida: cambiare finestra, minimizzare, ecc.

- Visualizzare texture di muro diverse (a tua scelta) che variano a seconda del lato verso cui è rivolto il muro (Nord, Sud, Est, Ovest).

- Il tuo programma deve essere in grado di impostare i colori del pavimento e del soffitto su due diversi.

- Il programma visualizza l'immagine in una finestra e rispetta le seguenti regole:
  - I tasti freccia sinistra e destra della tastiera devono permetterti di guardare a sinistra e a destra nel labirinto.
  - I tasti W, A, S e D devono permetterti di muovere il punto di vista attraverso il labirinto.
  - Premere ESC deve chiudere la finestra e uscire dal programma pulitamente.
  - Cliccare sulla croce rossa sulla cornice della finestra deve chiudere la finestra e uscire dal programma pulitamente.
  - L'uso di immagini della libreria minilibX è fortemente raccomandato.

- Il tuo programma deve prendere come primo argomento un file di descrizione della scena con estensione .cub.

### Requisiti della mappa:

- La mappa deve essere composta solo da 6 caratteri possibili:
  - `0` per uno spazio vuoto
  - `1` per un muro
  - `N`, `S`, `E` o `W` per la posizione di partenza e orientamento del giocatore

Esempio di mappa valida semplice:

111111
100101
101001
1100N1
111111

- La mappa deve essere chiusa/circondata da muri, altrimenti il programma deve restituire un errore.

- Tranne per il contenuto della mappa, ogni tipo di elemento può essere separato da una o più righe vuote.

- Tranne per il contenuto della mappa che deve sempre essere l'ultimo, ogni tipo di elemento può essere impostato in qualsiasi ordine nel file.

- Tranne per la mappa, ogni tipo di informazione di un elemento può essere separato da uno o più spazi.

- La mappa deve essere parsata come appare nel file. Gli spazi sono una parte valida della mappa e sta a te gestirli. Devi essere in grado di parsare qualsiasi tipo di mappa, purché rispetti le regole della mappa.

### Formato del file .cub:

Ogni elemento deve iniziare con il suo identificatore di tipo, seguito dalle sue informazioni specifiche:

**Texture Nord:**
NO ./percorso_texture_nord


- Se viene incontrata qualsiasi configurazione errata di qualsiasi tipo nel file, il programma deve uscire correttamente e restituire "Error\n" seguito da un messaggio di errore esplicito di tua scelta.

---

## Capitolo VI - Parte Bonus

⚠️ **I bonus saranno valutati solo se la tua parte obbligatoria è perfetta.**

Per perfetto intendiamo naturalmente che deve essere completa, che non può fallire, anche in casi di errori malevoli come uso scorretto, ecc. Significa che se la tua parte obbligatoria non ottiene TUTTI i punti durante la valutazione, i tuoi bonus saranno completamente IGNORATI.

### Lista dei bonus:
- Collisioni con i muri
- Un sistema di minimappa
- Porte che possono aprirsi e chiudersi
- Sprite animati
- Ruotare il punto di vista con il mouse

💡 Sarai in grado di creare giochi migliori più tardi, non sprecare troppo tempo!

ℹ️ Sei autorizzato a usare altre funzioni o aggiungere simboli sulla mappa per completare la parte bonus purché il loro uso sia giustificato durante la tua valutazione. Sei anche autorizzato a modificare il formato del file di scena previsto per adattarlo alle tue esigenze. Sii intelligente!

---
## Capitolo VIII - Consegna e peer-evaluation

Consegna il tuo compito nel tuo repository Git come al solito. Solo il lavoro all'interno del tuo repository sarà valutato durante la difesa. Non esitare a controllare due volte i nomi dei tuoi file per assicurarti che siano corretti.

Durante la valutazione, potrebbe essere occasionalmente richiesta una breve modifica del progetto. Questo potrebbe comportare un piccolo cambiamento di comportamento, alcune righe di codice da scrivere o riscrivere, o una funzionalità facile da aggiungere.

Anche se questo passaggio potrebbe non essere applicabile a ogni progetto, devi essere preparato se è menzionato nelle linee guida di valutazione.

Questo passaggio è pensato per verificare la tua effettiva comprensione di una parte specifica del progetto. La modifica può essere eseguita in qualsiasi ambiente di sviluppo tu scelga (ad esempio, la tua configurazione abituale), e dovrebbe essere fattibile entro pochi minuti - a meno che non sia definito un intervallo di tempo specifico come parte della valutazione.