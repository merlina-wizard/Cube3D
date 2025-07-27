#include "cube3d.h"

char	**read_file_lines(int fd)
{
	char	*line;
	char	*joined;
	char	**lines;

	joined = ft_strdup("");
	if (!joined)
		return (NULL);
	while ((line = get_next_line(fd)))
	{
		char *tmp = ft_strjoin(joined, line);
		free(joined);
		free(line);
		if (!tmp)
			return (NULL);
		joined = tmp;
	}
	lines = ft_split(joined, '\n');
	free(joined);
	return (lines);
}

void	print_map(char **map)
{
	int	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

#include "cube3d.h"

int	main(int argc, char **argv)
{
	t_game	game;
	char	**file_lines;
	int		fd;
	int		map_start;

	if (argc != 2)
		return (printf("Usage: ./maptest map.cub\n"), 1);

	init_game(&game);

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (printf("Errore apertura file\n"), 1);

	file_lines = read_file_lines(fd);
	if (!file_lines)
		return (printf("Errore lettura file\n"), 1);

	map_start = find_map_start(file_lines);
	if (map_start == -1)
		return (free_split(file_lines), printf("Map not found\n"), 1);

	// ⚠️ Prima inizializza MiniLibX, poi carica texture
	if (!init_mlx(&game))
		return (free_split(file_lines), free_all(&game), 1);

	if (!parse_render_info(&game, file_lines, map_start))
		return (free_split(file_lines), free_all(&game), 1);

	if (parse_map(&game, file_lines) != 0)
		return (free_split(file_lines), free_all(&game), 1);

	free_split(file_lines);

	printf("✅ Mappa e informazioni rendering caricate correttamente!\n");

	// 🎮 Hook eventi
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_hook(game.win, 17, 0, handle_exit, &game);         // click X
	mlx_hook(game.win, 2, 1L << 0, handle_key, &game);     // key press

	// 🌀 Avvia loop principale
	mlx_loop(game.mlx);

	return (0);
}
