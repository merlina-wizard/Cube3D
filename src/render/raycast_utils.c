/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:56:03 by lorenzo           #+#    #+#             */
/*   Updated: 2025/08/05 16:59:36 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/* Select which texture index to use */
int	select_tex(t_ray *r)
{
	if (r->side == 0 && r->ray_dir_x > 0)
		return (0);
	if (r->side == 0)
		return (1);
	if (r->ray_dir_y > 0)
		return (2);
	return (3);
}

void	cast_ray(t_game *g, int x)
{
	t_ray	*r;

	r = &g->ray;
	init_dir_dist(g, r, x);
	init_step_hit(g, r);
	perform_dda(g, r);
	finalize_dist(g, r);
}

void	init_dir_dist(t_game *g, t_ray *r, int x)
{
	double	cam_x;

	cam_x = 2.0 * x / g->win_w - 1.0;
	r->ray_dir_x = g->player.dir_x + g->player.plane_x * cam_x;
	r->ray_dir_y = g->player.dir_y + g->player.plane_y * cam_x;
	r->map_x = (int)g->player.x;
	r->map_y = (int)g->player.y;
	r->delta_dist_x = fabs(1.0 / r->ray_dir_x);
	r->delta_dist_y = fabs(1.0 / r->ray_dir_y);
}

/* Initialize step, sideDist and hit flag */
void	init_step_hit(t_game *g, t_ray *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (g->player.x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - g->player.x) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (g->player.y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - g->player.y) * r->delta_dist_y;
	}
	r->hit = 0;
}

/* Perform DDA to find wall hit */
void	perform_dda(t_game *g, t_ray *r)
{
	while (r->hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (g->map.grid[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}
