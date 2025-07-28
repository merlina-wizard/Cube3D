#include "cube3d.h"

/* Finish perpendicular distance calculation */
void finalize_dist(t_game *g, t_ray *r)
{
	if (r->side == 0)
		r->perp_dist = (r->mapX - g->player.x +
			(1 - r->stepX) / 2.0) / r->rayDirX;
	else
		r->perp_dist = (r->mapY - g->player.y +
			(1 - r->stepY) / 2.0) / r->rayDirY;
}

/* Calculate vertical slice start/end and height */
void calc_slice(t_game *g, t_ray *r,
	int *start, int *end, int *height)
{
	int h = g->win_h;
	*height = (int)(h / r->perp_dist);
	*start = -(*height) / 2 + h / 2;
	if (*start < 0)
		*start = 0;
	*end = (*height) / 2 + h / 2;
	if (*end >= h)
		*end = h - 1;
}

/* Compute exact wall hit x-coordinate for texture mapping */
double compute_wall_x(t_game *g, t_ray *r)
{
	double wall_x;
	if (r->side == 0)
		wall_x = g->player.y + r->perp_dist * r->rayDirY;
	else
		wall_x = g->player.x + r->perp_dist * r->rayDirX;
	return wall_x - floor(wall_x);
}

/* Draw the textured vertical slice */
void draw_slice(t_game *g, t_ray *r, int x)
{
	int start, end, hgt;
	calc_slice(g, r, &start, &end, &hgt);
	t_img *tex = &g->texture[select_tex(r)];
	double wall_x = compute_wall_x(g, r);
	int tex_x = (int)(wall_x * tex->width);
	if ((r->side == 0 && r->rayDirX > 0) ||
		(r->side == 1 && r->rayDirY < 0))
		tex_x = tex->width - tex_x - 1;
	double step = (double)tex->height / hgt;
	double pos = (start - g->win_h / 2 + hgt / 2) * step;
	int y = start;
	while (y <= end)
	{
		int ty = (int)pos % tex->height;
		int color = *(int *)(tex->data + ty * tex->size_line
			+ tex_x * 4);
		if (r->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		*(int *)(g->frame.data + y * g->frame.size_line
			+ x * 4) = color;
		pos += step;
		y++;
	}
}

void draw_wall_slice(t_game *g, int x, t_ray *r)
{
	draw_slice(g, r, x);
}
