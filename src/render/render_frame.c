/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:17:08 by lorenzo           #+#    #+#             */
/*   Updated: 2025/09/17 01:51:16 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

void	put_bg_pixel(t_game *g, t_coord pos, int sky, int floor)
{
	int	*pixel;

	pixel = (int *)(g->frame.data + (int)pos.y * g->frame.size_line
			+ (int)pos.x * 4);
	if ((int)pos.y < g->win_h / 2)
		*pixel = sky;
	else
		*pixel = floor;
}

void	draw_bg_color(t_game *g)
{
	t_coord	pos;
	int		sky;
	int		floor;

	sky = get_color(g->ceiling_c);
	floor = get_color(g->floor_c);
	pos.y = 0;
	while ((int)pos.y < g->win_h)
	{
		pos.x = 0;
		while ((int)pos.x < g->win_w)
		{
			put_bg_pixel(g, pos, sky, floor);
			pos.x++;
		}
		pos.y++;
	}
}

void	render_walls(t_game *g)
{
	int	x;

	x = 0;
	while (x < g->win_w)
	{
		cast_ray(g, x);
		draw_wall_slice(g, x, &g->ray);
		x++;
	}
}

int	render_frame(t_game *g)
{
	handle_mouse_rotation(g);
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
