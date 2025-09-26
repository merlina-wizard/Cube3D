/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:17:08 by lorenzo           #+#    #+#             */
/*   Updated: 2025/09/21 11:50:57 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	show_start_screen(t_game *g)
{
	mlx_string_put(g->mlx, g->win, g->win_w / 2 - 60,
		g->win_h / 2, 0xFFFFFF, "Press ENTER to start");
	if (!check_minimap_size(g))
		mlx_string_put(g->mlx, g->win, g->win_w / 2 - 70,
			g->win_h / 2 + 30, 0xFF0000, "Warning: Map too large");
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
	if (g->game_started && check_minimap_size(g))
		draw_minimap(g);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img_ptr, 0, 0);
	if (!g->game_started)
		show_start_screen(g);
	return (0);
}
