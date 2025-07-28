// init_game.c
#include "cube3d.h"

static void init_window_and_map(t_game *g)
{
	g->mlx = NULL;
	g->win = NULL;
	g->win_w = 800;
	g->win_h = 600;
	g->map.grid = NULL;
	g->map.width = 0;
	g->map.height = 0;
}

static void init_player_and_textures(t_game *g)
{
	int i = 0;

	g->player.x = 0;
	g->player.y = 0;
	g->player.dir_x = 0;
	g->player.dir_y = 0;
	g->player.plane_x = 0;
	g->player.plane_y = 0;
	g->player.move_speed = 0.1;
	g->player.rot_speed = 0.05;
	while (i < 4)
		g->texture[i++].img_ptr = NULL;
	g->floor_tex.img_ptr = NULL;
	g->ceiling_tex.img_ptr = NULL;
	g->floor_c = (t_color){-1, -1, -1};
	g->ceiling_c = (t_color){-1, -1, -1};
}

void init_game(t_game *g)
{
	init_window_and_map(g);
	init_player_and_textures(g);
}
