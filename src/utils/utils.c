/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 23:30:38 by lorenzo           #+#    #+#             */
/*   Updated: 2025/09/28 20:00:25 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error(char *message)
{
	printf("Error: %s\n", message);
	return (0);
}

int	error_exit(char *msg, t_game *g)
{
	printf("Error: %s\n", msg);
	free_all(g);
	exit(1);
	return (0);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || ft_strchr("NSEW", c) != NULL);
}

void	free_textures(t_game *g)
{
	int	i;

	i = 0;
	if (!g || !g->mlx)
		return ;
	while (i < 4)
	{
		if (g->texture[i].img_ptr)
			mlx_destroy_image(g->mlx, g->texture[i].img_ptr);
		i++;
	}
	if (g->floor_tex.img_ptr)
		mlx_destroy_image(g->mlx, g->floor_tex.img_ptr);
	if (g->ceiling_tex.img_ptr)
		mlx_destroy_image(g->mlx, g->ceiling_tex.img_ptr);
}

void	free_all(t_game *g)
{
	if (!g)
		return ;
	free_textures(g);
	if (g->mlx && g->frame.img_ptr)
		mlx_destroy_image(g->mlx, g->frame.img_ptr);
	free_minimap(g);
	if (g->mlx)
	{
		if (g->mouse_enabled)
		{
			mlx_mouse_show(g->mlx, g->win);
			g->mouse_enabled = 0;
		}
		if (g->win)
			mlx_destroy_window(g->mlx, g->win);
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
	g->win = NULL;
	g->mlx = NULL;
}
