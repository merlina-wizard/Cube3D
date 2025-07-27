#include "include/cube3d.h"
/*
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (printf("Usage: ./cub3D map.cub\n"), 1);

	init_game(&game);

	if (parse_cub_file(&game, argv[1]) != 0)
		return (free_all(&game), 1);

	if (init_mlx(&game) != 0)
		return (free_all(&game), 1);

	game_loop(&game); // hook, eventi, render loop

	free_all(&game);
	return (0);
}*/

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
		char *tmp = joined;
		joined = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
		if (!joined)
			return (NULL);
	}
	lines = ft_split(joined, '\n');
	free(joined);
	return (lines);
}

int	main(int argc, char **argv)
{
	t_game	game;
	char	**file_lines;
	int		fd;

	if (argc != 2)
		return (printf("Usage: ./maptest map.cub\n"), 1);

	init_game(&game);

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (printf("Errore apertura file\n"), 1);

	file_lines = read_file_lines(fd);
	if (!file_lines)
		return (printf("Errore lettura file\n"), 1);

	if (parse_map(&game, file_lines) != 0)
	{
		free_split(file_lines);
		return (printf("❌ Mappa non valida\n"), 1);
	}
	free_split(file_lines);
	printf("✅ Mappa valida!\n");
	return (0);
}
