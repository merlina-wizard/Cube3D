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

void move_player(t_game *g, int key)
{
	double ms = g->player.move_speed;
	double dx = 0.0, dy = 0.0;
	const double buffer = 0.1;

	// 1) Calcolo del vettore di movimento
	if (key == KEY_W || key == KEY_S) {
		if (key == KEY_W) {
			dx =  g->player.dir_x;
			dy =  g->player.dir_y;
		} else {
			dx = -g->player.dir_x;
			dy = -g->player.dir_y;
		}
	}
	else if (key == KEY_D || key == KEY_A) {
		if (key == KEY_D) {
			dx =  g->player.plane_x;
			dy =  g->player.plane_y;
		} else {
			dx = -g->player.plane_x;
			dy = -g->player.plane_y;
		}
	}

	// 2) Nuove posizioni “senza buffer”
	double new_x = g->player.x + dx * ms;
	double new_y = g->player.y + dy * ms;

	// 3) Calcolo dei punti di controllo con buffer
	double check_x = new_x;
	if (dx > 0.0)
		check_x += buffer;
	else if (dx < 0.0)
		check_x -= buffer;

	double check_y = new_y;
	if (dy > 0.0)
		check_y += buffer;
	else if (dy < 0.0)
		check_y -= buffer;

	// 4) Prova prima il movimento combinato
	if (!is_wall(g, check_y, check_x)) {
		g->player.x = new_x;
		g->player.y = new_y;
	}
	else {
		// 5a) Prova solo asse X (mantieni Y corrente)
		double check_x_only = new_x;
		if (dx > 0.0)
			check_x_only += buffer;
		else if (dx < 0.0)
			check_x_only -= buffer;

		if (!is_wall(g, g->player.y, check_x_only)) {
			g->player.x = new_x;
		}

		// 5b) Prova solo asse Y (mantieni X aggiornata)
		double check_y_only = new_y;
		if (dy > 0.0)
			check_y_only += buffer;
		else if (dy < 0.0)
			check_y_only -= buffer;

		if (!is_wall(g, check_y_only, g->player.x)) {
			g->player.y = new_y;
		}
	}
}

