/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 00:07:03 by lorenzo           #+#    #+#             */
/*   Updated: 2025/09/09 16:35:40 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_position_safe(t_map *map, int i, int j)
{
	if (i < 0 || i >= map->height || j < 0)
		return (0);
	if (j >= (int)ft_strlen(map->grid[i]))
		return (0);
	if (map->grid[i][j] == ' ')
	{
		if (i == 0 || i == map->height - 1)
			return (0);
		if (j == 0 || j >= map->width - 1)
			return (0);
	}
	return (1);
}

int	handle_player_found(t_player *p, int *p_count, int i, int j)
{
	if (*p_count > 0)
		return (error("Multiple players found"));
	(*p_count)++;
	p->x = j + 0.5;
	p->y = i + 0.5;
	return (1);
}

int	handle_cell(t_map *map, t_player *p, int *p_count, t_coord pos)
{
	char	c;

	c = map->grid[(int)pos.y][(int)pos.x];
	if (!is_valid_map_char(c))
		return (error("Invalid character in map"));
	if (ft_strchr("0NSEW", c))
	{
		if (!check_surroundings(map, (int)pos.y, (int)pos.x))
			return (error("Map has openings or invalid borders"));
	}
	if (ft_strchr("NSEW", c))
	{
		if (!handle_player_found(p, p_count, (int)pos.y, (int)pos.x))
			return (0);
		init_player_dir(c, p);
	}
	return (1);
}

int	validate_map_loop(t_map *map, int *p_count, t_player *p)
{
	t_coord	pos;

	pos.y = 0;
	while ((int)pos.y < map->height)
	{
		pos.x = 0;
		while (map->grid[(int)pos.y][(int)pos.x])
		{
			if (!handle_cell(map, p, p_count, pos))
				return (0);
			pos.x++;
		}
		pos.y++;
	}
	return (1);
}

int	validate_map(t_map *map, t_player *player)
{
	int	player_count;

	player_count = 0;
	print_map(map->grid);
	if (!validate_map_loop(map, &player_count, player))
		return (0);
	if (player_count != 1)
		return (error("Map must have exactly one player"));
	if (!validate_borders(map))
		return (error("Map is not closed by walls"));
	return (1);
}
