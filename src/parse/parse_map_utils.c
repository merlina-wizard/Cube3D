#include "cube3d.h"

int	count_map_lines(char **lines, int start)
{
	int	count = 0;

	while (lines[start + count])
		count++;
	return (count);
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
