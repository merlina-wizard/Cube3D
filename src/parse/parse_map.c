#include "cube3d.h"

char	**extract_map(char **lines, int start, int height)
{
	int		i;
	char	**map;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map[i] = ft_strdup(lines[start + i]);
		if (!map[i])
		{
			free_split(map);
			return (NULL);
		}
		i++;
	}
	map[height] = NULL;
	return (map);
}

int	load_tmp_map(char ***tmp_map, char **lines, int *start, int *height)
{
	*start = find_map_start(lines);
	if (*start == -1)
	{
		error("No map found");
		return (0);
	}
	*height = count_map_lines(lines, *start);
	*tmp_map = extract_map(lines, *start, *height);
	if (!*tmp_map)
	{
		error("Failed to extract map");
		return (0);
	}
	return (1);
}

int	parse_map(t_game *g, char **lines)
{
	int		start;
	int		height;
	char	**tmp_map;

	if (!load_tmp_map(&tmp_map, lines, &start, &height))
		return (1);
	if (!validate_map(tmp_map, height, &g->player))
	{
		free_split(tmp_map);
		return (1);
	}
	g->map.height = height;
	g->map.width = get_max_width(tmp_map, height);
	if (!alloc_map(&g->map, tmp_map))
	{
		free_split(tmp_map);
		return (1);
	}
	free_split(tmp_map);
	return (0);
}
