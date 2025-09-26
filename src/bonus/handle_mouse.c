/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:31:13 by lorenzo           #+#    #+#             */
/*   Updated: 2025/09/21 13:58:37 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	center_mouse(t_game *g)
{
	int	center_x;
	int	center_y;

	center_x = g->win_w / 2;
	center_y = g->win_h / 2;
	mlx_mouse_move(g->mlx, g->win, center_x, center_y);
}

void	toggle_mouse_control(t_game *g)
{
	g->mouse_enabled = !g->mouse_enabled;
	if (g->mouse_enabled)
	{
		mlx_mouse_hide(g->mlx, g->win);
		center_mouse(g);
		printf("Mouse control: ON\n");
	}
	else
	{
		mlx_mouse_show(g->mlx, g->win);
		printf("Mouse control: OFF\n");
	}
}

int	mouse_move_hook(int x, int y, t_game *g)
{
	static int	old_x = -1;
	int			delta_x;
	double		rotation_angle;

	if (!g->mouse_enabled)
		return (0);
	if (old_x == -1)
	{
		old_x = x;
		return (0);
	}
	delta_x = x - old_x;
	if (abs(delta_x) > 0)
	{
		rotation_angle = (double)delta_x * 0.002;
		rotate_player(&g->player, rotation_angle);
		old_x = x;
		if (x < 100 || x > g->win_w - 100)
		{
			mlx_mouse_move(g->mlx, g->win, g->win_w / 2, g->win_h / 2);
			old_x = g->win_w / 2;
		}
	}
	y = y;
	return (0);
}
