/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:21:51 by mamerlin          #+#    #+#             */
/*   Updated: 2025/09/03 14:46:55 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	handle_exit(t_game *g)
{
	free_all(g);
	exit(0);
	return (0);
}

int	handle_key(int key, t_game *g)
{
	if (key == KEY_ESC)
		handle_exit(g);
	else if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		move_player(g, key);
	else if (key == KEY_LEFT)
		rotate_player(&g->player, -g->player.rot_speed);
	else if (key == KEY_RIGHT)
		rotate_player(&g->player, g->player.rot_speed);
	return (0);
}

#define MOUSE_SENS 0.002

int	center_mouse(t_game *g, int cx, int cy)
{
	mlx_mouse_move(g->mlx, g->win, cx, cy);
	return (0);
}

void	handle_mouse_rotation_bonus(t_game *g)
{
	t_coord	center;
	int		mx;
	int		my;
	int		dx;
	double	angle;

	center.x = g->win_w / 2;
	center.y = g->win_h / 2;
	if (mlx_mouse_get_pos(g->mlx, g->win, &mx, &my) != 0)
		return ;
	dx = mx - (int)center.x;
	if (dx != 0)
	{
		angle = (double)dx * MOUSE_SENS;
		rotate_player(&g->player, angle);
		center_mouse(g, (int)center.x, (int)center.y);
	}
}
