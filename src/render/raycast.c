#include "cube3d.h"
#include <math.h>

void cast_ray(t_game *g, int x)
{
	t_ray *r = &g->ray;

	// calcolo del raggio nello spazio di proiezione
	double cameraX = 2.0 * x / (double)g->win_w - 1.0;
	r->rayDirX = g->player.dir_x + g->player.plane_x * cameraX;
	r->rayDirY = g->player.dir_y + g->player.plane_y * cameraX;

	// posizione della mappa
	r->mapX = (int)floor(g->player.x);
	r->mapY = (int)floor(g->player.y);

	// lunghezze distanze delta
	r->deltaDistX = fabs(1.0 / r->rayDirX);
	r->deltaDistY = fabs(1.0 / r->rayDirY);

	// calcolo step e sideDist iniziali
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

	// DDA
	r->hit = 0;
	while (!r->hit)
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

	// distanza perpendicolare (per evitare l’effetto fish‑eye)
	if (r->side == 0)
		r->perp_dist = (r->mapX - g->player.x + (1 - r->stepX) / 2.0) / r->rayDirX;
	else
		r->perp_dist = (r->mapY - g->player.y + (1 - r->stepY) / 2.0) / r->rayDirY;
}


void draw_wall_slice(t_game *g, int x)
{
	t_ray *r = &g->ray;

	// altezza della colonna da disegnare
	int lineHeight = (int)(g->win_h / r->perp_dist);

	// calcolo drawStart e drawEnd
	int drawStart = -lineHeight / 2 + g->win_h / 2;
	if (drawStart < 0) drawStart = 0;
	int drawEnd = lineHeight / 2 + g->win_h / 2;
	if (drawEnd >= g->win_h) drawEnd = g->win_h - 1;

	// shading semplice: scurisci i lati Y
	int color = g->texture[r->side].data[0];
	if (r->side == 1)
		color = (color >> 1) & 0x7F7F7F;

	// disegno della colonna
	for (int y = drawStart; y <= drawEnd; y++)
	{
		int *pixel = (int *)(g->frame.data
					   + y * g->frame.size_line
					   + x * 4);
		*pixel = color;
	}
}
