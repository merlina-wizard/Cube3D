/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:03:20 by lorenzo           #+#    #+#             */
/*   Updated: 2025/09/20 11:48:34 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	init_rgb(char *val, t_color *color, t_game *g)
{
	char	**rgb;

	rgb = ft_split(val, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (error_exit("Invalid color format, USE; R,G,B in .cub file", g));
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	free_split(rgb);
	if (color->r < 0 || color->r > 255
		|| color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (error_exit("RGB values must be 0-255 in .cub file", g));
	return (1);
}

int	parse_color_line(char *key, char *val, t_game *g)
{
	if (ft_strcmp(key, "F") == 0)
		init_rgb(val, &g->floor_c, g);
	else if (ft_strcmp(key, "C") == 0)
		init_rgb(val, &g->ceiling_c, g);
	return (1);
}

static int	get_texture_index(char *key)
{
	if (key[0] == 'N' && key[1] == 'O')
		return (0);
	if (key[0] == 'S' && key[1] == 'O')
		return (1);
	if (key[0] == 'W' && key[1] == 'E')
		return (2);
	if (key[0] == 'E' && key[1] == 'A')
		return (3);
	return (-1);
}

int	parse_render_info(t_game *g, char **lines, int map_start)
{
	int		i;
	char	**tok;
	int		tex_idx;

	i = -1;
	while (++i < map_start)
	{
		if (lines[i][0])
		{
			tok = ft_split(lines[i], ' ');
			if (!tok || !tok[0] || !tok[1])
				return (free_split(tok), error("Invalid info line"));
			parse_color_line(tok[0], tok[1], g);
			tex_idx = get_texture_index(tok[0]);
			if (tex_idx >= 0)
				load_texture(g->mlx, &g->texture[tex_idx], tok[1],
					"Failed to load wall texture");
			free_split(tok);
		}
	}
	return (1);
}
