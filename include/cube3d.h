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

int	handle_exit(t_game *g);
int	handle_key(int key, t_game *g);
int center_mouse(t_game *g, int cx, int cy);
void handle_mouse_rotation_bonus(t_game *g);
void init_game(t_game *g);
int mlx_boot(t_game *g);
int load_texture(void *mlx, t_img *t, char *path, char *msg);
int init_window_and_frame(t_game *g);
int	count_map_lines(char **lines, int start);
int	alloc_map(t_map *map, char **tmp_map);
int	is_map_line(const char *line);
void	free_split(char **split);
int	load_tmp_map(char ***tmp_map, char **lines, int *start, int *height);
int	parse_map(t_game *g, char **lines);
int ft_strcmp(const char *s1, const char *s2);
int is_color_key(char *k);
int parse_color_line(char *key, char *val, t_game *g);
int parse_render_info(t_game *g, char **lines, int map_start);
int validate_borders(char **map, int height,
							int width);
int check_top_bottom_borders(char **map, int height,
								   int width);
int check_side_borders(char **map, int height);
int check_side_borders(char **map, int height);
int check_surroundings(char **map, int h, int w,
							  int i, int j);
void	init_player_dir(char c, t_player *p);
int is_position_safe(char **map, int i, int j,
							 int height, int width);
int handle_cell(char **map, int h, int width,
					   int *p_count, t_player *p,
					   int i, int j);
int validate_map_loop(char **map, int h,
					  int *p_count, t_player *p);
int validate_map(char **map, int height,
				 t_player *player);
int is_wall(t_game *g, double y, double x);
void get_direction(t_game *g, int key, double *dx, double *dy);
double offset(double val, double dir, double buffer);
void try_move(t_game *g, double new_x, double new_y, double buffer);
void move_player(t_game *g, int key);
void rotate_player(t_player *p, double angle);
int select_tex(t_ray *r);
void cast_ray(t_game *g, int x);
void init_dir_dist(t_game *g, t_ray *r, int x);
void init_step_hit(t_game *g, t_ray *r);
void perform_dda(t_game *g, t_ray *r);
void finalize_dist(t_game *g, t_ray *r);
void calc_slice(t_game *g, t_ray *r,
	int *start, int *end, int *height);
double compute_wall_x(t_game *g, t_ray *r);
void draw_slice(t_game *g, t_ray *r, int x);
void draw_wall_slice(t_game *g, int x, t_ray *r);
void draw_bg_tex(t_game *g);
void draw_tex_pixel(t_game *g, int x, int y);
t_img *get_tex(t_game *g, int y);
int get_sky_color(t_color c);
void put_bg_pixel(t_game *g, int x, int y, int sky, int floor);
void draw_bg_color(t_game *g);
void render_walls(t_game *g);
int render_frame(t_game *g);
int	find_map_start(char **lines);
int	error(char *message);
int	is_valid_map_char(char c);
int	is_valid_map_char(char c);
int	get_max_width(char **map, int height);
void	free_textures(t_game *g);
void	free_all(t_game *g);
void print_map(char **map);

#endif
