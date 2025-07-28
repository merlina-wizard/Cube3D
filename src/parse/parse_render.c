// parse_render_info.c
#include "cube3d.h"

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int is_color_key(char *k)
{
	return (!ft_strcmp(k, "F") || !ft_strcmp(k, "C"));
}

int parse_color_line(char *key, char *val, t_game *g)
{
	char **rgb;
	if (!ft_strncmp(val + ft_strlen(val) - 4, ".xpm", 4))
	{
		t_img *t = (key[0] == 'F') ? &g->floor_tex : &g->ceiling_tex;
		return load_texture(g->mlx, t, val, "Failed to load floor/ceiling texture");
	}
	rgb = ft_split(val, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_split(rgb), error("Invalid color format"));
	g->floor_c.r = ft_atoi(rgb[0]);
	g->floor_c.g = ft_atoi(rgb[1]);
	g->floor_c.b = ft_atoi(rgb[2]);
	free_split(rgb);
	return 1;
}

int parse_render_info(t_game *g, char **lines, int map_start)
{
	int i = 0;
	char **tok;

	while (i < map_start)
	{
		if (lines[i][0])
		{
			tok = ft_split(lines[i], ' ');
			if (!tok || !tok[0] || !tok[1])
				return (free_split(tok), error("Invalid info line"));
			if (is_color_key(tok[0]))
				parse_color_line(tok[0], tok[1], g);
			else
				load_texture(g->mlx,
					&g->texture[(tok[0][1]=='O'? (tok[0][0]=='N'?0:1):(tok[0][0]=='W'?2:3))],
					tok[1], "Failed to load wall texture");
			free_split(tok);
		}
		i++;
	}
	return 1;
}
