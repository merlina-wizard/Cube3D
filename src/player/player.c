#include "cube3d.h"

static int is_wall(t_game *g, double y, double x)
{
	int iy = (int)y;
	int ix = (int)x;

	if (iy < 0 || iy >= g->map.height)
		return (1);
	if (ix < 0 || ix >= (int)ft_strlen(g->map.grid[iy]))
		return (1);
	return (g->map.grid[iy][ix] == '1');
}

static void get_direction(t_game *g, int key, double *dx, double *dy)
{
	if (key == KEY_W)
	{
		*dx = g->player.dir_x;
		*dy = g->player.dir_y;
	}
	else if (key == KEY_S)
	{
		*dx = -g->player.dir_x;
		*dy = -g->player.dir_y;
	}
	else if (key == KEY_D)
	{
		*dx = g->player.plane_x;
		*dy = g->player.plane_y;
	}
	else if (key == KEY_A)
	{
		*dx = -g->player.plane_x;
		*dy = -g->player.plane_y;
	}
	else
	{
		*dx = 0.0;
		*dy = 0.0;
	}
}

static double offset(double val, double dir, double buffer)
{
	if (dir > 0.0)
		return val + buffer;
	if (dir < 0.0)
		return val - buffer;
	return val;
}

static void try_move(t_game *g, double new_x, double new_y, double buffer)
{
	double dx = new_x - g->player.x;
	double dy = new_y - g->player.y;
	double check_x = offset(new_x, dx, buffer);
	double check_y = offset(new_y, dy, buffer);

	if (!is_wall(g, check_y, check_x))
	{
		g->player.x = new_x;
		g->player.y = new_y;
	}
	else
	{
		double check_x_only = offset(new_x, dx, buffer);
		double check_y_only = offset(new_y, dy, buffer);
		if (!is_wall(g, g->player.y, check_x_only))
			g->player.x = new_x;
		if (!is_wall(g, check_y_only, g->player.x))
			g->player.y = new_y;
	}
}

void move_player(t_game *g, int key)
{
	double dx;
	double dy;
	double ms = g->player.move_speed;
	double new_x;
	double new_y;
	const double buffer = 0.1;

	get_direction(g, key, &dx, &dy);
	new_x = g->player.x + dx * ms;
	new_y = g->player.y + dy * ms;
	try_move(g, new_x, new_y, buffer);
}
