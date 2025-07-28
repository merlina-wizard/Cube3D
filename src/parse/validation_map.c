#include "cube3d.h"

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

int is_position_safe(char **map, int i, int j,
							 int height, int width)
{
	if (i < 0 || i >= height || j < 0 || j >= (int)ft_strlen(map[i]))
		return 0;
	if (map[i][j] == ' ' &&
		(i == 0 || i == height - 1 || j == 0 || j >= width - 1))
		return 0;
	return 1;
}

int handle_cell(char **map, int h, int width,
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
