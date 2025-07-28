#include "cube3d.h"

static int get_sky_color(t_color c)
{
	return (c.r << 16) | (c.g << 8) | c.b;
}

static void put_bg_pixel(t_game *g, int x, int y, int sky, int floor)
{
	int *pixel;

	pixel = (int *)(g->frame.data + y * g->frame.size_line + x * 4);
	if (y < g->win_h / 2)
		*pixel = sky;
	else
		*pixel = floor;
}

static void draw_bg_color(t_game *g)
{
	int y;
	int x;
	int sky;
	int floor;

	sky = get_sky_color(g->ceiling_c);
	floor = get_sky_color(g->floor_c);
	y = 0;
	while (y < g->win_h)
	{
		x = 0;
		while (x < g->win_w)
		{
			put_bg_pixel(g, x, y, sky, floor);
			x++;
		}
		y++;
	}
}

static t_img *get_tex(t_game *g, int y)
{
	if (y < g->win_h / 2)
		return (&g->ceiling_tex);
	return (&g->floor_tex);
}

static void draw_tex_pixel(t_game *g, int x, int y)
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

static void draw_bg_tex(t_game *g)
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

void render_walls(t_game *g)
{
	int x;

	x = 0;
	while (x < g->win_w)
	{
		cast_ray(g, x);
		draw_wall_slice(g, x, &g->ray);
		x++;
	}
}

int render_frame(t_game *g)
{
	if (!g->frame.img_ptr)
		return (0);
	if (g->ceiling_tex.img_ptr && g->floor_tex.img_ptr)
		draw_bg_tex(g);
	else
		draw_bg_color(g);
	render_walls(g);
	handle_mouse_rotation_bonus(g);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img_ptr, 0, 0);
	return (0);
}
