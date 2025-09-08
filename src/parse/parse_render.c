/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:03:20 by lorenzo           #+#    #+#             */
/*   Updated: 2025/09/02 00:39:11 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	is_color_key(char *k)
{
	return (!ft_strcmp(k, "F") || !ft_strcmp(k, "C"));
}

int	parse_color_line(char *key, char *val, t_game *g)
{
	char	**rgb;
	t_img	*t;

	if (key[0] == 'F')
		t = &g->floor_tex;
	else
		t = &g->ceiling_tex;
	if (!ft_strncmp(val + ft_strlen(val) - 4, ".xpm", 4))
		return (load_texture(g->mlx, t, val, "Failed to load texture"));
	rgb = ft_split(val, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_split(rgb), error("Invalid color format"));
	g->floor_c.r = ft_atoi(rgb[0]);
	g->floor_c.g = ft_atoi(rgb[1]);
	g->floor_c.b = ft_atoi(rgb[2]);
	free_split(rgb);
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
			if (is_color_key(tok[0]))
				parse_color_line(tok[0], tok[1], g);
			else
			{
				tex_idx = get_texture_index(tok[0]);
				if (tex_idx >= 0)
					load_texture(g->mlx, &g->texture[tex_idx], tok[1],
						"Failed to load wall texture");
			}
			free_split(tok);
		}
	}
	return (1);
}
