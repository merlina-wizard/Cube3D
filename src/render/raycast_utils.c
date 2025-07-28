#include "cube3d.h"

/* Select which texture index to use */
int select_tex(t_ray *r)
{
	if (r->side == 0 && r->rayDirX > 0)
		return 0;
	if (r->side == 0)
		return 1;
	if (r->rayDirY > 0)
		return 2;
	return 3;
}

void cast_ray(t_game *g, int x)
{
	t_ray *r = &g->ray;
	init_dir_dist(g, r, x);
	init_step_hit(g, r);
	perform_dda(g, r);
	finalize_dist(g, r);
}

void init_dir_dist(t_game *g, t_ray *r, int x)
{
	double camX = 2.0 * x / g->win_w - 1.0;
	r->rayDirX = g->player.dir_x + g->player.plane_x * camX;
	r->rayDirY = g->player.dir_y + g->player.plane_y * camX;
	r->mapX = (int)g->player.x;
	r->mapY = (int)g->player.y;
	r->deltaDistX = fabs(1.0 / r->rayDirX);
	r->deltaDistY = fabs(1.0 / r->rayDirY);
}


/* Initialize step, sideDist and hit flag */
void init_step_hit(t_game *g, t_ray *r)
{
	if (r->rayDirX < 0)
	{
		r->stepX = -1;
		r->sideDistX = (g->player.x - r->mapX) * r->deltaDistX;
	}
	else
	{
		r->stepX = 1;
		r->sideDistX = (r->mapX + 1.0 - g->player.x) * r->deltaDistX;
	}
	if (r->rayDirY < 0)
	{
		r->stepY = -1;
		r->sideDistY = (g->player.y - r->mapY) * r->deltaDistY;
	}
	else
	{
		r->stepY = 1;
		r->sideDistY = (r->mapY + 1.0 - g->player.y) * r->deltaDistY;
	}
	r->hit = 0;
}

/* Perform DDA to find wall hit */
void perform_dda(t_game *g, t_ray *r)
{
	while (r->hit == 0)
	{
		if (r->sideDistX < r->sideDistY)
		{
			r->sideDistX += r->deltaDistX;
			r->mapX += r->stepX;
			r->side = 0;
		}
		else
		{
			r->sideDistY += r->deltaDistY;
			r->mapY += r->stepY;
			r->side = 1;
		}
		if (g->map.grid[r->mapY][r->mapX] == '1')
			r->hit = 1;
	}
}
