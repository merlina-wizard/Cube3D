#ifndef PLAYER_H
#define PLAYER_H

typedef struct s_player {
	int num;
	double x; // posizione x del giocatore
	double y; // posizione y del giocatore
	double dir_x; // componente x della direzione del giocatore
	double dir_y; // componente y della direzione del giocatore
	double plane_x;   // piano visivo orizzontale (per FOV)
	double plane_y;   // piano visivo verticale (per FOV)
	double move_speed;
	double rot_speed;

} t_player;

#endif
