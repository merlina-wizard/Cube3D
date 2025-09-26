/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:21:51 by mamerlin          #+#    #+#             */
/*   Updated: 2025/09/21 19:28:17 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_exit(t_game *g)
{
	free_all(g);
	exit(0);
	return (0);
}

int	handle_key(int key, t_game *g)
{
	if (key == KEY_ENTER && !g->game_started)
	{
		g->game_started = 1;
		return (0);
	}
	if (!g->game_started)
		return (0);
	else if (key == KEY_ESC)
		handle_exit(g);
	else if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		move_player(g, key);
	else if (key == KEY_LEFT)
		rotate_player(&g->player, -g->player.rot_speed);
	else if (key == KEY_RIGHT)
		rotate_player(&g->player, g->player.rot_speed);
	else if (key == 'm' || key == 'M')
		toggle_mouse_control(g);
	return (0);
}
