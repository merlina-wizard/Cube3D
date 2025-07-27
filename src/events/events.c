#include "cube3d.h"

int	handle_exit(t_game *g)
{
	free_all(g);
	exit(0);
	return (0);
}

int	handle_key(int key, t_game *g)
{
	if (key == KEY_ESC)
		handle_exit(g);
	else if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		move_player(g, key);
	return (0);
}
