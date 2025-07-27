        Avvio del programma
               │
           main.c
               ▼
      Parsing del file .cub
               │
  ┌────────────┴────────────┐
  │                         │
Parsing delle texture   Parsing della mappa
colori soffitto/pav.     (e validazione)
  │                         │
  └────────────┬────────────┘
               ▼
       Inizializzazione
         struttura dati
               ▼
   Inizializzazione MiniLibX
 (finestra, immagini, hook)
               ▼
      Ciclo di rendering
         (loop principale)
               ▼
    ┌────────────────────┐
    │ Ogni frame (tick): │
    └────────────────────┘
         │           ▲
         ▼           │
  Gestione input  Movimento player
         │           │
         ▼           ▼
    Calcolo Raycasting
         │
         ▼
    Disegno dell'immagine
 (pareti, colori, texture…)
         │
         ▼
    Visualizzazione a schermo
               │
               ▼
      Fine programma (ESC, X)
         └─> free() e exit()


struttura include:

	t_game → la struttura principale con tutti i dati del gioco

	t_player → posizione e direzione del giocatore

	t_map → mappa come matrice di caratteri

	t_img → immagine MLX per texture e rendering

	t_color → colore RGB per floor/ceiling
