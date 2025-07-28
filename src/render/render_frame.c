#include "cube3d.h"

static void	draw_bg_color(t_game *g)
{
	int y;
	int x;
	int *pixel;
	int sky;
	int floor;

	sky = (g->ceiling_c.r << 16) | (g->ceiling_c.g << 8) | g->ceiling_c.b;
	floor = (g->floor_c.r << 16) | (g->floor_c.g << 8) | g->floor_c.b;
	y = 0;
	while (y < g->win_h)
	{
		x = 0;
		while (x < g->win_w)
		{
			pixel = (int *)(g->frame.data + y * g->frame.size_line + x * 4);
			if (y < g->win_h / 2)
				*pixel = sky;
			else
				*pixel = floor;
			x++;
		}
		y++;
	}
}

static void	draw_bg_tex(t_game *g)
{
	int		x;
	int		y;
	int		tex_x;
	int		tex_y;
	int		*pixel;
	int		color;
	t_img	*tex;

	y = 0;
	while (y < g->win_h)
	{
		x = 0;
		while (x < g->win_w)
		{
			if (y < g->win_h / 2)
				tex = &g->ceiling_tex;
			else
				tex = &g->floor_tex;
			tex_y = (y < g->win_h / 2) ? (y * tex->height) / (g->win_h / 2)
									  : ((y - g->win_h / 2) * tex->height) / (g->win_h / 2);
			tex_x = (x * tex->width) / g->win_w;
			color = *(int *)(tex->data + tex_y * tex->size_line + tex_x * 4);
			pixel = (int *)(g->frame.data + y * g->frame.size_line + x * 4);
			*pixel = color;
			x++;
		}
		y++;
	}
}

void	render_walls(t_game *g)
{
	int x = 0;
	while (x < g->win_w)
	{
		cast_ray(g, x);
		draw_wall_slice(g, x, &g->ray);
		x++;
	}
}

int	render_frame(t_game *g)
{
	if (!g->frame.img_ptr)
		return (0);
	if (g->ceiling_tex.img_ptr && g->floor_tex.img_ptr)
		draw_bg_tex(g);
	else
		draw_bg_color(g);
	render_walls(g);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img_ptr, 0, 0);
	return (0);
}
