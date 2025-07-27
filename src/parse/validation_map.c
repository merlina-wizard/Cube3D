#include "cube3d.h"

int	is_position_safe(char **map, int i, int j, int height, int width)
{
	if (i < 0 || i >= height || j < 0 || j >= (int)ft_strlen(map[i]))
		return (0);
	if (map[i][j] == ' ' && (i == 0 || i == height - 1 ||
		j == 0 || j >= width - 1))
		return (0);
	return (1);
}

int	check_surroundings(char **map, int height, int width, int i, int j)
{
	int	di[] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int	dj[] = {-1, 0, 1, -1, 1, -1, 0, 1};
	int	k;

	k = 0;
	while (k < 8)
	{
		if (!is_position_safe(map, i + di[k], j + dj[k], height, width))
			return (0);
		k++;
	}
	return (1);
}

int	validate_borders(char **map, int height, int width)
{
	int	i;

	i = 0;
	while (i < height)
	{
		if (map[i][0] != '1' && map[i][0] != ' ')
			return (0);
		if (map[i][ft_strlen(map[i]) - 1] != '1' &&
			map[i][ft_strlen(map[i]) - 1] != ' ')
			return (0);
		i++;
	}
	i = 0;
	while (i < width && map[0][i] && map[height - 1][i])
	{
		if ((map[0][i] != '1' && map[0][i] != ' ') ||
			(map[height - 1][i] != '1' && map[height - 1][i] != ' '))
			return (0);
		i++;
	}
	return (1);
}

int	validate_map(char **map, int height, t_player *player)
{
	int	i, j, player_count, width;

	width = get_max_width(map, height);
	player_count = 0;
	i = 0;
	print_map(map);
	while (i < height)
	{
		j = 0;
		while (map[i][j])
		{
			char c = map[i][j];
			if (!is_valid_map_char(c))
				return (error("Invalid character in map"));

			if (ft_strchr("0NSEW", c) && !check_surroundings(map, height, width, i, j))
				return (error("Map has openings or invalid borders"));

			if (ft_strchr("NSEW", c))
			{
				if (player_count++ > 0)
					return (error("Multiple players found"));
				player->x = j + 0.5;
				player->y = i + 0.5;
				init_player_dir(c, player);
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (error("Map must have exactly one player"));
	if (!validate_borders(map, height, width))
		return (error("Map is not closed by walls"));
	return (1);
}
