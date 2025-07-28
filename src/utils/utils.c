#include "cube3d.h"

void print_map(char **map)
{
	int	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
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
	int	i = 0;
	int	max = 0;
	int	current;

	while (i < height)
	{
		current = ft_strlen(map[i]);
		if (current > max)
			max = current;
		i++;
	}
	return (max);
}

void	free_textures(t_game *g)
{
	int	i = 0;

	if (!g || !g->mlx)
		return;
	while (i < 4)
	{
		if (g->texture[i].img_ptr)
			mlx_destroy_image(g->mlx, g->texture[i].img_ptr);
		i++;
	}
	if (g->floor_tex.img_ptr)
		mlx_destroy_image(g->mlx, g->floor_tex.img_ptr);
	if (g->ceiling_tex.img_ptr)
		mlx_destroy_image(g->mlx, g->ceiling_tex.img_ptr);
}

void	free_all(t_game *g)
{
	int	i = 0;

	if (!g)
		return;
	free_textures(g);
	if (g->mlx && g->frame.img_ptr)
		mlx_destroy_image(g->mlx, g->frame.img_ptr);
	if (g->map.grid)
	{
		while (i < g->map.height && g->map.grid[i])
			free(g->map.grid[i++]);
		free(g->map.grid);
		g->map.grid = NULL;
	}
	if (g->mlx)
	{
		if (g->win)
			mlx_destroy_window(g->mlx, g->win);
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
	g->mlx = NULL;
	g->win = NULL;
}
