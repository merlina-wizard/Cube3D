/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:54:27 by lorenzo           #+#    #+#             */
/*   Updated: 2025/09/26 11:08:41 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_minimap_square(t_game *g, int start_x, int start_y, int color)
{
	int	x;
	int	y;
	int	size;

	size = MINIMAP_SCALE - 1;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			put_minimap_pixel(g, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

void	put_minimap_pixel(t_game *g, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= g->win_w || y < 0 || y >= g->win_h)
		return ;
	dst = g->frame.data + (y * g->frame.size_line + x * 4);
	*(unsigned int *)dst = color;
}

int	check_minimap_size(t_game *g)
{
	int	map_pixel_width;
	int	map_pixel_height;

	map_pixel_width = g->map.width * MINIMAP_SCALE;
	map_pixel_height = g->map.height * MINIMAP_SCALE;
	if (map_pixel_width > MINIMAP_SIZE || map_pixel_height > MINIMAP_SIZE)
		return (0);
	return (1);
}

void	draw_minimap_warning(t_game *g)
{
	int		x;
	int		y;
	char	*msg;

	msg = "Map too large for minimap";
	x = MINIMAP_OFFSET;
	y = MINIMAP_OFFSET + 10;
	mlx_string_put(g->mlx, g->win, x, y, C_MINIMAP_WALL, msg);
}
