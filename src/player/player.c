#include "cube3d.h"

static int	is_wall(t_game *g, double y, double x)
{
	int iy = (int)y;
	int ix = (int)x;

	if (iy < 0 || iy >= g->map.height)
		return (1);
	if (ix < 0 || ix >= (int)ft_strlen(g->map.grid[iy]))
		return (1);
	return (g->map.grid[iy][ix] == '1');
}

void	move_player(t_game *g, int key)
{
	double ms = g->player.move_speed;
	double dx = 0, dy = 0;

	if (key == KEY_W || key == KEY_S)
	{
		dx = g->player.dir_x * (key == KEY_W ? 1 : -1);
		dy = g->player.dir_y * (key == KEY_W ? 1 : -1);
	}
	else if (key == KEY_A || key == KEY_D)
	{
		dx = g->player.plane_x * (key == KEY_D ? 1 : -1);
		dy = g->player.plane_y * (key == KEY_D ? 1 : -1);
	}
	if (!is_wall(g, g->player.y, g->player.x + dx * ms))
		g->player.x += dx * ms;
	if (!is_wall(g, g->player.y + dy * ms, g->player.x))
		g->player.y += dy * ms;
}
