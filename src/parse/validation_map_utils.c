/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:05:19 by lorenzo           #+#    #+#             */
/*   Updated: 2025/09/21 19:21:37 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_borders(t_map *map)
{
	if (!check_side_borders(map))
		return (0);
	if (!check_top_bottom_borders(map))
		return (0);
	return (1);
}

int	check_top_bottom_borders(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->width && map->grid[0][i] && map->grid[map->height - 1][i])
	{
		if ((map->grid[0][i] != '1' && map->grid[0][i] != ' ') ||
			(map->grid[map->height - 1][i] != '1'
				&& map->grid[map->height - 1][i] != ' '))
			return (0);
		i++;
	}
	return (1);
}

int	check_side_borders(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		if (map->grid[i][0] != '1' && map->grid[i][0] != ' ')
			return (0);
		if (map->grid[i][ft_strlen(map->grid[i]) - 1] != '1' &&
			map->grid[i][ft_strlen(map->grid[i]) - 1] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	init_direction_arrays(int *di, int *dj)
{
	di[0] = -1;
	di[1] = -1;
	di[2] = -1;
	di[3] = 0;
	di[4] = 0;
	di[5] = 1;
	di[6] = 1;
	di[7] = 1;
	dj[0] = -1;
	dj[1] = 0;
	dj[2] = 1;
	dj[3] = -1;
	dj[4] = 1;
	dj[5] = -1;
	dj[6] = 0;
	dj[7] = 1;
}

int	check_surroundings(t_map *map, int i, int j)
{
	int	di[8];
	int	dj[8];
	int	k;

	init_direction_arrays(di, dj);
	k = 0;
	while (k < 8)
	{
		if (!is_position_safe(map, i + di[k], j + dj[k]))
			return (0);
		k++;
	}
	return (1);
}
