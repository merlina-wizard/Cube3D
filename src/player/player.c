/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:36:58 by lorenzo           #+#    #+#             */
/*   Updated: 2025/09/17 14:09:52 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_game *g, double y, double x)
{
	int	iy;
	int	ix;

	iy = (int)y;
	ix = (int)x;
	if (iy < 0 || iy >= g->map.height)
		return (1);
	if (ix < 0 || ix >= (int)ft_strlen(g->map.grid[iy]))
		return (1);
	return (g->map.grid[iy][ix] == '1');
}

void	get_direction(t_game *g, int key, double *dx, double *dy)
{
	if (key == KEY_W)
	{
		*dx = g->player.dir_x;
		*dy = g->player.dir_y;
	}
	else if (key == KEY_S)
	{
		*dx = -g->player.dir_x;
		*dy = -g->player.dir_y;
	}
	else if (key == KEY_D)
	{
		*dx = g->player.plane_x;
		*dy = g->player.plane_y;
	}
	else if (key == KEY_A)
	{
		*dx = -g->player.plane_x;
		*dy = -g->player.plane_y;
	}
	else
	{
		*dx = 0.0;
		*dy = 0.0;
	}
}

void	try_move(t_game *g, double new_x, double new_y, double buffer)
{
	t_coord	delta;
	t_coord	check;

	delta.x = new_x - g->player.x;
	delta.y = new_y - g->player.y;
	check.x = offset(new_x, delta.x, buffer);
	check.y = offset(new_y, delta.y, buffer);
	if (!is_wall(g, check.y, check.x))
	{
		g->player.x = new_x;
		g->player.y = new_y;
		return ;
	}
	check.x = offset(new_x, delta.x, buffer);
	if (!is_wall(g, g->player.y, check.x))
		g->player.x = new_x;
	check.y = offset(new_y, delta.y, buffer);
	if (!is_wall(g, check.y, g->player.x))
		g->player.y = new_y;
}

void	move_player(t_game *g, int key)
{
	t_coord	dir;
	t_coord	new_pos;
	double	ms;
	double	buffer;

	ms = g->player.move_speed;
	buffer = 0.1;
	get_direction(g, key, &dir.x, &dir.y);
	new_pos.x = g->player.x + dir.x * ms;
	new_pos.y = g->player.y + dir.y * ms;
	try_move(g, new_pos.x, new_pos.y, buffer);
}

void	rotate_player(t_player *p, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_a;
	double	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos_a - p->dir_y * sin_a;
	p->dir_y = old_dir_x * sin_a + p->dir_y * cos_a;
	p->plane_x = p->plane_x * cos_a - p->plane_y * sin_a;
	p->plane_y = old_plane_x * sin_a + p->plane_y * cos_a;
}
