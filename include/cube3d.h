#ifndef CUBE3D_H
#define CUBE3D_H

#include "libft/libft.h"
#include "gnl/get_next_line.h"
#include "events.h"
#include "map.h"
#include "player.h"
#include "render.h"
#include "utils.h"
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>
#include <fcntl.h>


typedef struct s_game {
	void *mlx; //puntatore a mlx
	void *win; //puntatore alla finestra
	int win_w; // larghezza
	int win_h; // altezza

	t_map map; // mappa caricata da .cub
	t_player player; // giocatore(posizione, direzione, etc.)
	t_img texture[4]; // texture per il rendering (NO, SO, WE, EA)
	t_color floor_c; // colori del pavimento e del soffitto
	t_color ceiling_c; // colori del soffitto
	t_img frame;

} t_game;


void	init_game (t_game *g);
int	parse_map(t_game *g, char **lines);
void	free_split(char **split);

#endif
