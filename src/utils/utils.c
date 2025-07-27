#include "cube3d.h"

int	error(char *message)
{
	printf("Error: %s\n", message);
	return (0);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || ft_strchr("NSEW", c) != NULL);
}

int	get_max_width(char **map, int height)
{
	int	i;
	int	max;
	int	current;

	i = 0;
	max = 0;
	while (i < height)
	{
		current = ft_strlen(map[i]);
		if (current > max)
			max = current;
		i++;
	}
	return (max);
}

void	free_all(t_game *g)
{
	if (g->mlx)
	{
		if (g->frame.img_ptr)
			mlx_destroy_image(g->mlx, g->frame.img_ptr);
		if (g->win)
			mlx_destroy_window(g->mlx, g->win);
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
	for (int i = 0; i < 4; i++)
	{
		if (g->texture[i].img_ptr)
			mlx_destroy_image(g->mlx, g->texture[i].img_ptr);
	}
	free(g->map.grid);
}
