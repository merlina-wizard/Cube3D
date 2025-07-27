#include "cube3d.h"

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static int	parse_color(char *line, t_color *color)
{
	char	**rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_split(rgb), error("Invalid color format"));

	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	free_split(rgb);

	if (color->r < 0 || color->r > 255 ||
		color->g < 0 || color->g > 255 ||
		color->b < 0 || color->b > 255)
		return (error("RGB values out of range"));

	return (1);
}

static int	parse_texture(t_game *g, char *key, char *path)
{
	int i = -1;

	if (!ft_strcmp(key, "NO"))
		i = TEX_NO;
	else if (!ft_strcmp(key, "SO"))
		i = TEX_SO;
	else if (!ft_strcmp(key, "WE"))
		i = TEX_WE;
	else if (!ft_strcmp(key, "EA"))
		i = TEX_EA;

	if (i == -1)
		return (error("Invalid texture identifier"));

	g->texture[i].img_ptr = mlx_xpm_file_to_image(g->mlx, path,
		&g->texture[i].width, &g->texture[i].height);
	if (!g->texture[i].img_ptr)
		return (error("Failed to load texture"));
	g->texture[i].data = mlx_get_data_addr(g->texture[i].img_ptr,
		&g->texture[i].bpp, &g->texture[i].size_line, &g->texture[i].endian);

	return (1);
}

static int	is_color_key(char *key)
{
	return (!ft_strcmp(key, "F") || !ft_strcmp(key, "C"));
}

static int	parse_color_line(char *key, char *value, t_game *g)
{
	t_img *tex;

	// Se è una texture (contiene ".xpm")
	if (ft_strnstr(value, ".xpm", ft_strlen(value)))
	{
		tex = (!ft_strcmp(key, "F")) ? &g->floor_tex : &g->ceiling_tex;
		tex->img_ptr = mlx_xpm_file_to_image(g->mlx, value, &tex->width, &tex->height);
		if (!tex->img_ptr)
			return (error("Failed to load floor/ceiling texture"));
		tex->data = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->size_line, &tex->endian);
		return (1);
	}
	// Altrimenti è un colore RGB
	if (!ft_strcmp(key, "F"))
		return (parse_color(value, &g->floor_c));
	else if (!ft_strcmp(key, "C"))
		return (parse_color(value, &g->ceiling_c));
	return (error("Unknown color key"));
}

int	parse_render_info(t_game *g, char **lines, int map_start)
{
	int		i;
	char	**tokens;

	i = 0;
	while (i < map_start)
	{
		if (lines[i][0] != '\0')
		{
			tokens = ft_split(lines[i], ' ');
			if (!tokens || !tokens[0] || !tokens[1])
				return (free_split(tokens), error("Invalid info line"));
			if (is_color_key(tokens[0]))
			{
				if (!parse_color_line(tokens[0], tokens[1], g))
					return (free_split(tokens), 0);
			}
			else if (!parse_texture(g, tokens[0], tokens[1]))
				return (free_split(tokens), 0);
			free_split(tokens);
		}
		i++;
	}
	return (1);
}
