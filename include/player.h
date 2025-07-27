#ifndef PLAYER_H
#define PLAYER_H

typedef struct s_player {
	double x; // posizione x del giocatore
	double y; // posizione y del giocatore
	double dir_x; // componente x della direzione del giocatore
	double dir_y; // componente y della direzione del giocatore
	double move_speed;
	double rot_speed;

} t_player;

#endif
