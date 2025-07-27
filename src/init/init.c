#include "cube3d.h"
int	init_mlx(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		return (error("mlx_init failed"));

	g->win_w = 800;
	g->win_h = 600;
	g->win = mlx_new_window(g->mlx, g->win_w, g->win_h, "cub3D");
	if (!g->win)
		return (error("mlx_new_window failed"));

	g->frame.img_ptr = mlx_new_image(g->mlx, g->win_w, g->win_h);
	if (!g->frame.img_ptr)
		return (error("Failed to create frame buffer"));

	g->frame.data = mlx_get_data_addr(g->frame.img_ptr,
		&g->frame.bpp, &g->frame.size_line, &g->frame.endian);

		g->floor_tex.img_ptr = mlx_xpm_file_to_image(g->mlx, "assets/textures/floor.xpm",
		&g->floor_tex.width, &g->floor_tex.height);
	if (!g->floor_tex.img_ptr)
		return (error("Failed to load floor texture"));

	g->floor_tex.data = mlx_get_data_addr(g->floor_tex.img_ptr,
		&g->floor_tex.bpp, &g->floor_tex.size_line, &g->floor_tex.endian);

	g->ceiling_tex.img_ptr = mlx_xpm_file_to_image(g->mlx, "assets/textures/sky2.xpm",
		&g->ceiling_tex.width, &g->ceiling_tex.height);
	if (!g->ceiling_tex.img_ptr)
		return (error("Failed to load ceiling texture"));

	g->ceiling_tex.data = mlx_get_data_addr(g->ceiling_tex.img_ptr,
		&g->ceiling_tex.bpp, &g->ceiling_tex.size_line, &g->ceiling_tex.endian);

	return (1);
}


void	init_game (t_game *g)
{
	g->mlx = NULL;
	g->win = NULL;
	g->win_w = 800;
	g->win_h = 600;

	g->map.grid = NULL;
	g->map.width = 0;
	g->map.height = 0;

	g->player.x = 0;
	g->player.y = 0;
	g->player.dir_x = 0;
	g->player.dir_y = 0;
	g->player.plane_x = 0;
	g->player.plane_y = 0;
	g->player.move_speed = 0.1;
	g->player.rot_speed = 0.05;

	for (int i = 0; i < 4; i++)
		g->texture[i].img_ptr = NULL;

	g->floor_c = (t_color){-1, -1, -1};
	g->ceiling_c = (t_color){-1, -1, -1};

}
