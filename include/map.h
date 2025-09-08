/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:20:46 by lorenzo           #+#    #+#             */
/*   Updated: 2025/09/02 00:59:53 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <mlx.h>

typedef struct s_map
{
	char	**grid; // rappresentazione della mappa
	int		width; // larghezza della mappa
	int		height; // altezza della mappa
}	t_map;

typedef struct s_map_data
{
	int	height;
	int	width;
	int	i;
	int	j;
	int	*p_count;
}	t_map_data;

#endif
