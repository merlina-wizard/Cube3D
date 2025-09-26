/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:35:42 by lorenzo           #+#    #+#             */
/*   Updated: 2025/09/26 11:15:38 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_grid(t_game *g)
{
	int	x;
	int	y;
	int	color;
	int	px;
	int	py;

	y = -1;
	while (++y < g->map.height && y * MINIMAP_SCALE < MINIMAP_SIZE)
	{
		x = -1;
		while (++x < g->map.width && x * MINIMAP_SCALE < MINIMAP_SIZE)
		{
			px = MINIMAP_OFFSET + x * MINIMAP_SCALE;
			py = MINIMAP_OFFSET + y * MINIMAP_SCALE;
			if (g->map.grid[y][x] == '1')
				color = C_MINIMAP_WALL;
			else
				color = C_MINIMAP_FLOOR;
			draw_minimap_square(g, px, py, color);
		}
	}
}

void	draw_player_circle(t_game *g, int px, int py)
{
	int	dx;
	int	dy;

	dy = -MINIMAP_PLAYER;
	while (dy <= MINIMAP_PLAYER)
	{
		dx = -MINIMAP_PLAYER;
		while (dx <= MINIMAP_PLAYER)
		{
			if (dx * dx + dy * dy <= MINIMAP_PLAYER * MINIMAP_PLAYER)
				put_minimap_pixel(g, px + dx, py + dy, C_MINIMAP_PLAYER);
			dx++;
		}
		dy++;
	}
}

void	draw_player_fov(t_game *g, int px, int py)
{
	int	i;
	int	left_x;
	int	left_y;
	int	right_x;
	int	right_y;

	i = 0;
	while (i < 20)
	{
		left_x = px + (int)((g->player.dir_x - g->player.plane_x) * i);
		left_y = py + (int)((g->player.dir_y - g->player.plane_y) * i);
		right_x = px + (int)((g->player.dir_x + g->player.plane_x) * i);
		right_y = py + (int)((g->player.dir_y + g->player.plane_y) * i);
		put_minimap_pixel(g, left_x, left_y, C_MINIMAP_FOV);
		put_minimap_pixel(g, right_x, right_y, C_MINIMAP_FOV);
		i++;
	}
}

void	draw_minimap_player(t_game *g)
{
	int	px;
	int	py;

	px = MINIMAP_OFFSET + (int)(g->player.x * MINIMAP_SCALE);
	py = MINIMAP_OFFSET + (int)(g->player.y * MINIMAP_SCALE);
	draw_player_circle(g, px, py);
	draw_player_fov(g, px, py);
}

void	draw_minimap(t_game *g)
{
	if (!check_minimap_size(g))
	{
		draw_minimap_warning(g);
		return ;
	}
	draw_minimap_grid(g);
	draw_minimap_player(g);
}
