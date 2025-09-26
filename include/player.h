/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:19:03 by lorenzo           #+#    #+#             */
/*   Updated: 2025/09/17 15:40:19 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

typedef struct s_player
{
	int		num;
	double	x; // posizione x del giocatore
	double	y; // posizione y del giocatore
	double	dir_x; // componente x della direzione del giocatore
	double	dir_y; // componente y della direzione del giocatore
	double	plane_x; // componente x del piano di proiezione
	double	plane_y; // componente y del piano di proiezione
	double	move_speed;
	double	rot_speed;
}	t_player;

#endif
