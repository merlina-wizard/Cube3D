#include "cube3d.h"

void draw_bg_tex(t_game *g)
{
	int x;
	int y;

	y = 0;
	while (y < g->win_h)
	{
		x = 0;
		while (x < g->win_w)
		{
			draw_tex_pixel(g, x, y);
			x++;
		}
		y++;
	}
}

void draw_tex_pixel(t_game *g, int x, int y)
{
	t_img *tex;
	int tex_x;
	int tex_y;
	int color;
	int *pixel;

	tex = get_tex(g, y);
	if (y < g->win_h / 2)
		tex_y = (y * tex->height) / (g->win_h / 2);
	else
		tex_y = ((y - g->win_h / 2) * tex->height) / (g->win_h / 2);
	tex_x = (x * tex->width) / g->win_w;
	color = *(int *)(tex->data + tex_y * tex->size_line + tex_x * 4);
	pixel = (int *)(g->frame.data + y * g->frame.size_line + x * 4);
	*pixel = color;
}

t_img *get_tex(t_game *g, int y)
{
	if (y < g->win_h / 2)
		return (&g->ceiling_tex);
	return (&g->floor_tex);
}
