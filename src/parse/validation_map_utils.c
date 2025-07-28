#include "cube3d.h"

int validate_borders(char **map, int height,
							int width)
{
	if (!check_side_borders(map, height))
		return 0;
	if (!check_top_bottom_borders(map, height, width))
		return 0;
	return 1;
}

int check_top_bottom_borders(char **map, int height,
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

int check_side_borders(char **map, int height)
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

int check_surroundings(char **map, int h, int w,
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
