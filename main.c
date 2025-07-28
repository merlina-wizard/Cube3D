#include "cube3d.h"


static int open_and_read_file(const char *p, char ***out)
{
	int fd = open(p, O_RDONLY);
	char *joined = ft_strdup("");
	char *line, *tmp; char **split;

	if (fd < 0 || !joined)
		return error("File open or malloc failed");
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strjoin(joined, line);
		free(joined), free(line);
		if (!tmp)
			return error("Join failed");
		joined = tmp;
		line = get_next_line(fd);
	}
	close(fd);
	split = ft_split(joined, '\n');
	free(joined);
	if (!split)
		return error("Split failed");
	*out = split;
	return 1;
}

static int parse_all(t_game *g, char **lines)
{
	int ms = find_map_start(lines);
	if (ms < 0)
		return (free_split(lines), error("Map not found"));
	if (!parse_render_info(g, lines, ms))
		return (free_split(lines), 0);
	if (parse_map(g, lines) != 0)
		return (free_split(lines), 0);
	free_split(lines);
	return 1;
}

int check_missing_wall_textures(t_game *g)
{
	int i = 0;
	while (i < 4)
		if (!g->texture[i++].img_ptr)
			return error("Missing one of NO/SO/WE/EA");
	return 1;
}

int main(int ac, char **av)
{
	t_game g;
	char **file_lines;

	if (ac != 2)
		return printf("Usage: ./cub3D map.cub\n"), 1;
	init_game(&g);
	if (!open_and_read_file(av[1], &file_lines))
		return free_all(&g), 1;
	if (!mlx_boot(&g))
		return free_split(file_lines), free_all(&g), 1;
	if (!parse_all(&g, file_lines))
		return free_all(&g), 1;
	if (!check_missing_wall_textures(&g))
		return free_all(&g), 1;
	if (!init_window_and_frame(&g))
		return free_all(&g), 1;
	printf("✅ Mappa e info rendering caricate!\n");
	mlx_loop_hook(g.mlx, render_frame, &g);
	mlx_hook(g.win, 17, 0, handle_exit, &g);
	mlx_hook(g.win, 2, 1L<<0, handle_key, &g);
	mlx_loop(g.mlx);
	return 0;
}
