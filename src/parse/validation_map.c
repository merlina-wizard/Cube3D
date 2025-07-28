#include "cube3d.h"

static int is_position_safe(char **map, int i, int j,
							 int height, int width)
{
	if (i < 0 || i >= height || j < 0 || j >= (int)ft_strlen(map[i]))
		return 0;
	if (map[i][j] == ' ' &&
		(i == 0 || i == height - 1 || j == 0 || j >= width - 1))
		return 0;
	return 1;
}

static int check_surroundings(char **map, int h, int w,
							  int i, int j)
{
	int di[] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int dj[] = {-1, 0, 1, -1, 1, -1, 0, 1};
	int k;

	k = 0;
	while (k < 8)
	{
		if (!is_position_safe(map, i + di[k], j + dj[k], h, w))
			return 0;
		k++;
	}
	return 1;
}

static int check_side_borders(char **map, int height)
{
	int i;

	i = 0;
	while (i < height)
	{
		if (map[i][0] != '1' && map[i][0] != ' ')
			return 0;
		if (map[i][ft_strlen(map[i]) - 1] != '1' &&
			map[i][ft_strlen(map[i]) - 1] != ' ')
			return 0;
		i++;
	}
	return 1;
}

static int check_top_bottom_borders(char **map, int height,
								   int width)
{
	int i;

	i = 0;
	while (i < width && map[0][i] && map[height - 1][i])
	{
		if ((map[0][i] != '1' && map[0][i] != ' ') ||
			(map[height - 1][i] != '1' && map[height - 1][i] != ' '))
			return 0;
		i++;
	}
	return 1;
}

static int validate_borders(char **map, int height,
							int width)
{
	if (!check_side_borders(map, height))
		return 0;
	if (!check_top_bottom_borders(map, height, width))
		return 0;
	return 1;
}

static int handle_cell(char **map, int h, int width,
					   int *p_count, t_player *p,
					   int i, int j)
{
	char c;

	c = map[i][j];
	if (!is_valid_map_char(c))
		return error("Invalid character in map");
	if (ft_strchr("0NSEW", c))
	{
		if (!check_surroundings(map, h, width, i, j))
			return error("Map has openings or invalid borders");
	}
	if (ft_strchr("NSEW", c))
	{
		if (*p_count > 0)
			return error("Multiple players found");
		(*p_count)++;
		p->x = j + 0.5;
		p->y = i + 0.5;
		init_player_dir(c, p);
	}
	return 1;
}

int validate_map_loop(char **map, int h,
					  int *p_count, t_player *p)
{
	int i;
	int j;
	int width;

	width = get_max_width(map, h);
	i = 0;
	while (i < h)
	{
		j = 0;
		while (map[i][j])
		{
			if (!handle_cell(map, h, width, p_count, p, i, j))
				return 0;
			j++;
		}
		i++;
	}
	return 1;
}

int validate_map(char **map, int height,
				 t_player *player)
{
	int player_count;
	int width;

	player_count = 0;
	print_map(map);
	if (!validate_map_loop(map, height, &player_count, player))
		return 0;
	if (player_count != 1)
		return error("Map must have exactly one player");
	width = get_max_width(map, height);
	if (!validate_borders(map, height, width))
		return error("Map is not closed by walls");
	return 1;
}
