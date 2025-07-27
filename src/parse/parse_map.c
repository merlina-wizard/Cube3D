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
	if (!line || *line == '\0')
		return (0);
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
	int	i = 0;

	while (lines[i])
	{
		if (is_map_line(lines[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	count_map_lines(char **lines, int start)
{
	int	count = 0;

	while (lines[start + count])
		count++;
	return (count);
}

char	**extract_map(char **lines, int start, int height)
{
	int		i;
	char	**map;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	for (i = 0; i < height; i++)
	{
		map[i] = ft_strdup(lines[start + i]);
		if (!map[i])
			return (free_split(map), NULL);
	}
	map[height] = NULL;
	return (map);
}

void	init_player_dir(char c, t_player *p)
{
	if (c == 'N')
		(p->dir_x = -1, p->dir_y = 0, p->plane_x = 0, p->plane_y = 0.66);
	else if (c == 'S')
		(p->dir_x = 1, p->dir_y = 0, p->plane_x = 0, p->plane_y = -0.66);
	else if (c == 'E')
		(p->dir_x = 0, p->dir_y = 1, p->plane_x = 0.66, p->plane_y = 0);
	else if (c == 'W')
		(p->dir_x = 0, p->dir_y = -1, p->plane_x = -0.66, p->plane_y = 0);
}

int	alloc_map(t_map *map, char **tmp_map)
{
	int	i;

	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (0);
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = ft_strdup(tmp_map[i]);
		if (!map->grid[i])
		{
			while (i > 0)
				free(map->grid[--i]);
			free(map->grid);
			return (0);
		}
		i++;
	}
	map->grid[map->height] = NULL;
	return (1);
}

int	parse_map(t_game *g, char **lines)
{
	int		start;
	int		height;
	char	**tmp_map;

	start = find_map_start(lines);
	if (start == -1)
		return (error("No map found"), 1);

	height = count_map_lines(lines, start);
	tmp_map = extract_map(lines, start, height);
	if (!tmp_map)
		return (error("Failed to extract map"), 1);

	if (!validate_map(tmp_map, height, &g->player))
		return (free_split(tmp_map), 1);

	g->map.height = height;
	g->map.width = get_max_width(tmp_map, height);
	if (!alloc_map(&g->map, tmp_map))
		return (free_split(tmp_map), 1);

	return (free_split(tmp_map), 0);
}
