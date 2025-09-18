/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:21:01 by lorenzo           #+#    #+#             */
/*   Updated: 2025/09/02 01:28:50 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include "events.h"
# include "map.h"
# include "player.h"
# include "render.h"
# include "utils.h"
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <limits.h>
# include <stdint.h>
# include <fcntl.h>

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_dist;
}	t_ray;

typedef struct s_game
{
	void		*mlx; //puntatore a mlx
	void		*win; //puntatore alla finestra
	int			win_w; // larghezza
	int			win_h; // altezza
	t_map		map; // mappa caricata da .cub
	t_player	player; // giocatore(posizione, direzione, etc.)
	t_img		texture[4]; // texture per il rendering (NO, SO, WE, EA)
	t_color		floor_c; // colori del pavimento e del soffitto
	t_color		ceiling_c; // colori del soffitto
	t_img		ceiling_tex;
	t_img		floor_tex; // texture del pavimento e del soffitt
	t_img		frame;
	t_ray		ray; // struttura per il raycasting
	int			mouse_enabled; // Flag per controllo mouse attivo
}	t_game;

//events.c
int		handle_exit(t_game *g);
int		handle_key(int key, t_game *g);
void	toggle_mouse_control(t_game *g);
void	center_mouse(t_game *g);
void	handle_mouse_rotation(t_game *g);
int		mouse_move_hook(int x, int y, t_game *g);
//
//init_game.c
void	init_game(t_game *g);
//
//init_mlx.c
int		mlx_boot(t_game *g);
int		load_texture(void *mlx, t_img *t, char *path, char *msg);
int		init_window_and_frame(t_game *g);
//
//parse_map_utils.c
int		count_map_lines(char **lines, int start);
int		alloc_map(t_map *map, char **tmp_map);
int		is_map_line(const char *line);
void	free_split(char **split);
//
//parse_map.c
char	**extract_map(char **lines, int start, int height);
int		load_tmp_map(char ***tmp_map, char **lines, int *start, int *height);
int		parse_map(t_game *g, char **lines);
//
//parse_Render.c
int		ft_strcmp(const char *s1, const char *s2);
int		init_rgb(char *val, t_color *color, t_game *g);
int		parse_color_line(char *key, char *val, t_game *g);
int		parse_render_info(t_game *g, char **lines, int map_start);
//
//validation_map_utils.c
int		validate_borders(t_map *map);
int		check_top_bottom_borders(t_map *map);
int		check_side_borders(t_map *map);
void	init_direction_arrays(int *di, int *dj);
int		check_surroundings(t_map *map, int i, int j);
//
//validation_map.c
int		is_position_safe(t_map *map, int i, int j);
int		handle_player_found(t_player *p, int *p_count, int i, int j);
int		handle_cell(t_map *map, t_player *p, int *p_count, t_coord pos);
int		validate_map_loop(t_map *map, int *p_count, t_player *p);
int		validate_map(t_map *map, t_player *player);
//
//player.c
int		is_wall(t_game *g, double y, double x);
void	get_direction(t_game *g, int key, double *dx, double *dy);
double	offset(double val, double dir, double buffer);
void	try_move(t_game *g, double new_x, double new_y, double buffer);
void	move_player(t_game *g, int key);
void	rotate_player(t_player *p, double angle);
//
//raycast_utils.c
int		select_tex(t_ray *r);
void	cast_ray(t_game *g, int x);
void	init_dir_dist(t_game *g, t_ray *r, int x);
void	init_step_hit(t_game *g, t_ray *r);
void	perform_dda(t_game *g, t_ray *r);
//
//raycast.c
void	finalize_dist(t_game *g, t_ray *r);
void	calc_slice(t_game *g, t_ray *r, t_slice_info *s);
double	compute_wall_x(t_game *g, t_ray *r);
void	draw_vertical_line(t_game *g, t_ray *r, t_slice_info *s, int x);
void	draw_wall_slice(t_game *g, int x, t_ray *r);
//
//render_frame_utils.c
void	draw_bg_tex(t_game *g);
void	draw_tex_pixel(t_game *g, int x, int y);
t_img	*get_tex(t_game *g, int y);
//
//render_frame.c
int		get_color(t_color c);
void	put_bg_pixel(t_game *g, t_coord pos, int sky, int floor);
void	draw_bg_color(t_game *g);
void	render_walls(t_game *g);
int		render_frame(t_game *g);
//
//utils/utils2l
void	print_map(char **map);
int		error(char *message);
int		error_exit(char *msg, t_game *g);
int		is_valid_map_char(char c);
void	free_textures(t_game *g);
void	free_all(t_game *g);
void	init_player_dir(char c, t_player *p);
int		get_max_width(char **map, int height);
int		find_map_start(char **lines);

#endif
