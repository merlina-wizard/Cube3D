#include "cube3d.h"
#include <math.h>

void	move_player(t_game *g, int key)
{
	double	move_step = g->player.move_speed;
	double	new_x, new_y;

	if (key == KEY_W)
	{
		new_x = g->player.x + g->player.dir_x * move_step;
		new_y = g->player.y + g->player.dir_y * move_step;
	}
	else if (key == KEY_S)
	{
		new_x = g->player.x - g->player.dir_x * move_step;
		new_y = g->player.y - g->player.dir_y * move_step;
	}
	else if (key == KEY_A)
	{
		new_x = g->player.x - g->player.plane_x * move_step;
		new_y = g->player.y - g->player.plane_y * move_step;
	}
	else if (key == KEY_D)
	{
		new_x = g->player.x + g->player.plane_x * move_step;
		new_y = g->player.y + g->player.plane_y * move_step;
	}
	else
		return;

	// Verifica collisioni
	if (g->map.grid[(int)new_y][(int)new_x] != '1')
	{
		g->player.x = new_x;
		g->player.y = new_y;
	}
}
