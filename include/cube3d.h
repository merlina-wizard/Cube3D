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

typedef struct s_ray {
	double rayDirX, rayDirY;
	int mapX, mapY;
	double sideDistX, sideDistY;
	double deltaDistX, deltaDistY;
	int stepX, stepY;
	int hit, side;
	double perp_dist;
} t_ray;

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
	t_img ceiling_tex;
	t_img floor_tex; // texture del pavimento e del soffitt
	t_img frame;
	t_ray ray; // struttura per il raycasting

} t_game;


void	init_game (t_game *g);
int		parse_map(t_game *g, char **lines);
int		find_map_start(char **lines);
void	free_split(char **split);
void	init_player_dir(char c, t_player *p);
int		validate_map(char **map, int height, t_player *player);
void	 print_map(char **map);
int		parse_render_info(t_game *g, char **lines, int map_start);
int		render_frame(t_game *g);
int		init_mlx(t_game *g);
int		handle_key(int key, t_game *g);
int		handle_exit(t_game *g);
int		error(char *message);
int		get_max_width(char **map, int height);
int		is_valid_map_char(char c);
void	free_all(t_game *g);
void	move_player(t_game *g, int key);
int		init_window_and_frame(t_game *g);
int		mlx_boot(t_game *g);
int load_texture(void *mlx, t_img *t, char *path, char *msg);
void draw_wall_slice(t_game *g, int x, t_ray *r);
void cast_ray(t_game *g, int x);

#endif
