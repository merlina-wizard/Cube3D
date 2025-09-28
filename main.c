/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:55:40 by lorenzo           #+#    #+#             */
/*   Updated: 2025/09/28 18:54:16 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	open_and_read_file(const char *p, char ***out)
{
	int		fd;
	char	*joined;
	char	*line;
	char	*tmp;

	fd = open(p, O_RDONLY);
	joined = ft_strdup("");
	if (fd < 0 || !joined)
		return (free(joined), error("File open or malloc failed"));
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strjoin(joined, line);
		free(joined);
		free(line);
		if (!tmp)
			return (close(fd), error("Join failed"));
		joined = tmp;
		line = get_next_line(fd);
	}
	close(fd);
	*out = ft_split(joined, '\n');
	if (!*out)
		return (free(joined), error("Split failed"));
	return (free(joined), 1);
}

static int	parse_all(t_game *g, char **lines)
{
	int	ms;

	ms = find_map_start(lines);
	if (ms < 0)
		return (free_split(lines), error("Map not found"));
	if (!parse_render_info(g, lines, ms))
		return (free_split(lines), 0);
	if (parse_map(g, lines) != 0)
		return (free_split(lines), 0);
	free_split(lines);
	return (1);
}

int	check_missing_wall_textures(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
		if (!g->texture[i++].img_ptr)
			return (error("Missing one of NO/SO/WE/EA"));
	return (1);
}

int	main(int ac, char **av)
{
	t_game	g;
	char	**file_lines;

	if (ac != 2)
		return (printf("Usage: ./cub3D map.cub\n"), 1);
	init_game(&g);
	if (!open_and_read_file(av[1], &file_lines))
		return (free_all(&g), 1);
	if (!mlx_boot(&g))
		return (free_split(file_lines), free_all(&g), 1);
	if (!parse_all(&g, file_lines))
		return (free_all(&g), 1);
	if (!check_missing_wall_textures(&g))
		return (free_all(&g), 1);
	if (!init_window_and_frame(&g))
		return (free_all(&g), 1);
	printf("✅ Mappa e info rendering caricate!\n");
	mlx_loop_hook(g.mlx, render_frame, &g);
	mlx_hook(g.win, 17, 0, handle_exit, &g);
	mlx_hook(g.win, 2, 1L << 0, handle_key, &g);
	mlx_hook(g.win, 6, 1L << 6, mouse_move_hook, &g);
	mlx_loop(g.mlx);
	free_all(&g);
	return (0);
}
