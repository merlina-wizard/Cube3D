#include "cube3d.h"

void	clear_image(t_game *g, int color)
{
	int	x, y;
	int	*pixel;

	y = 0;
	while (y < g->win_h)
	{
		x = 0;
		while (x < g->win_w)
		{
			pixel = (int *)(g->frame.data + y * g->frame.size_line + x * 4);
			*pixel = color;
			x++;
		}
		y++;
	}
}

int	render_frame(t_game *g)
{
	clear_image(g, 0x000000); // sfondo nero

	for (int y = 0; y < g->win_h; y++)
	{
		for (int x = 0; x < g->win_w; x++)
		{
			t_img *tex;
			int tex_x, tex_y;
			int color;

			// Se siamo nella metà superiore → usa sky
			if (y < g->win_h / 2)
			{
				tex = &g->ceiling_tex;
				tex_y = (y * tex->height) / (g->win_h / 2);
			}
			// Se siamo nella metà inferiore → usa floor
			else
			{
				tex = &g->floor_tex;
				tex_y = ((y - g->win_h / 2) * tex->height) / (g->win_h / 2);
			}
			tex_x = (x * tex->width) / g->win_w;

			color = *(int *)(tex->data + tex_y * tex->size_line + tex_x * 4);
			int *pixel = (int *)(g->frame.data + y * g->frame.size_line + x * 4);
			*pixel = color;
		}
	}
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img_ptr, 0, 0);
	printf("Pos: %f, %f\n", g->player.x, g->player.y);
	return (0);
}
