#include "cube3d.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	is_map_line(const char *line)
{
	while (*line)
	{
		if (!ft_strchr(" 01NSEW", *line))
			return (0);
		line++;
	}
	return (1);
}

int	find_map_start(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (is_map_line(lines[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	count_map_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines[i] && is_map_line(lines[i]))
		i++;
	return (i);
}

char	**extract_map(char **lines, int start, int height)
{
	int		i;
	char	**map;

	i = 0;
	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	while (i < height)
	{
		map[i] = ft_strdup(lines[start + i]);
		if (!map[i])
			return (free_split(map), NULL);
		i++;
	}
	map[height] = NULL;
	return (map);
}

void	init_player_dir(char c, t_player *p)
{
	if (c == 'N')
	{
		p->dir_x = -1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	else if (c == 'S')
	{
		p->dir_x = 1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
	else if (c == 'E')
	{
		p->dir_x = 0;
		p->dir_y = 1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else if (c == 'W')
	{
		p->dir_x = 0;
		p->dir_y = -1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
}

int	set_player(t_player *player, int i, int j, char c)
{
	player->x = j + 0.5;
	player->y = i + 0.5;
	init_player_dir(c, player);
	return (1);
}

int	validate_map_line(char *line, int i, t_player *p, int *count)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (ft_strchr("NSEW", line[j]))
		{
			if (*count)
				return (error("Troppi player"));
			*count += set_player(p, i, j, line[j]);
		}
		else if (!ft_strchr("01 ", line[j]))
			return (error("Carattere non valido"));
		j++;
	}
	return (1);
}

int	validate_map(char **map, int height, t_player *player)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < height)
	{
		if (!validate_map_line(map[i], i, player, &count))
			return (0);
		i++;
	}
	if (count != 1)
		return (error("Errore Player"));
	return (1);
}

int	parse_map(t_game *g, char **lines)
{
	int		start;
	int		height;
	char	**tmp_map;

	start = find_map_start(lines);
	if (start == -1)
		return (error("Mappa non trovata"));
	height = count_map_lines(&lines[start]);
	tmp_map = extract_map(lines, start, height);
	if (!tmp_map)
		return (error("Errore allocazione"));
	if (!validate_map(tmp_map, height, &g->player))
		return (free_split(tmp_map), 1);
	g->map.height = height;
	g->map.width = get_max_width(tmp_map, height);
	if (!alloc_map(&g->map, tmp_map))
		return (free_split(tmp_map), error("Errore allocazione mappa"));
	return (free_split(tmp_map), 0);
}
