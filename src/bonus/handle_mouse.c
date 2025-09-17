/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:31:13 by lorenzo           #+#    #+#             */
/*   Updated: 2025/09/09 16:34:01 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MOUSE_SENS 0.001

// Centra il mouse nella finestra
void	center_mouse(t_game *g)
{
	int	center_x;
	int	center_y;

	center_x = g->win_w / 2;
	center_y = g->win_h / 2;
	mlx_mouse_move(g->mlx, g->win, center_x, center_y);
}

// Attiva/disattiva controllo mouse
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

// Gestisce il movimento del mouse - USA rotate_player ESISTENTE!
void	handle_mouse_rotation(t_game *g)
{
	int		current_x;
	int		current_y;
	int		delta_x;
	int		center_x;
	double	rotation_angle;

	if (!g->mouse_enabled)
		return ;
	if (mlx_mouse_get_pos(g->mlx, g->win, &current_x, &current_y) != 0)
		return ;
	center_x = g->win_w / 2;
	delta_x = current_x - center_x;
	if (abs(delta_x) < 3)
		return ;
	rotation_angle = (double)delta_x * MOUSE_SENS;
	rotate_player(&g->player, rotation_angle);
	center_mouse(g);
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
		rotation_angle = (double)delta_x * 0.003;
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
