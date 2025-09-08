/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 00:41:49 by lorenzo           #+#    #+#             */
/*   Updated: 2025/09/02 00:55:36 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_player_dir(char c, t_player *p)
{
	p->dir_x = 1;
	p->dir_y = 0;
	p->plane_x = 0;
	p->plane_y = 0.66;
	if (c == 'S')
		p->plane_y = -0.66;
	else if (c == 'E')
	{
		p->dir_x = 0;
		p->dir_y = 1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else if (c == 'W')
	{
		p->dir_x = 0;
		p->dir_y = -1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
}

double	offset(double val, double dir, double buffer)
{
	if (dir > 0.0)
		return (val + buffer);
	if (dir < 0.0)
		return (val - buffer);
	return (val);
}

int	get_max_width(char **map, int height)
{
	int	i;
	int	max;
	int	current;

	i = 0;
	max = 0;
	while (i < height)
	{
		current = ft_strlen(map[i]);
		if (current > max)
			max = current;
		i++;
	}
	return (max);
}

int	find_map_start(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (is_map_line(lines[i]))
			return (i);
		i++;
	}
	return (-1);
}
