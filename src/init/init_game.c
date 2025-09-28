/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:58:49 by lorenzo           #+#    #+#             */
/*   Updated: 2025/09/27 18:38:10 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *g)
{
	int	i;

	i = 0;
	memset(g, 0, sizeof(*g));
	g->win_w = 800;
	g->win_h = 600;
	g->player.move_speed = 0.1;
	g->player.rot_speed = 0.05;
	while (i < 4)
		g->texture[i++].img_ptr = NULL;
	g->floor_c = (t_color){-1, -1, -1};
	g->ceiling_c = (t_color){-1, -1, -1};
}
