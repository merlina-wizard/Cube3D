// init_mlx.c
#include "cube3d.h"

int mlx_boot(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		return error("mlx_init failed");
	return 1;
}

int load_texture(void *mlx, t_img *t, char *path, char *msg)
{
	t->img_ptr = mlx_xpm_file_to_image(mlx, path, &t->width, &t->height);
	if (!t->img_ptr)
		return error(msg);
	t->data = mlx_get_data_addr(t->img_ptr,
		&t->bpp, &t->size_line, &t->endian);
	return 1;
}

int init_window_and_frame(t_game *g)
{
	g->win = mlx_new_window(g->mlx, g->win_w, g->win_h, "cub3D");
	if (!g->win)
		return error("mlx_new_window failed");
	g->frame.img_ptr = mlx_new_image(g->mlx, g->win_w, g->win_h);
	if (!g->frame.img_ptr)
		return error("Failed to create frame buffer");
	g->frame.data = mlx_get_data_addr(g->frame.img_ptr,
		&g->frame.bpp, &g->frame.size_line, &g->frame.endian);
	return 1;
}
