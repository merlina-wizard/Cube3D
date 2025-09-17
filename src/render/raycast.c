/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:05:33 by lorenzo           #+#    #+#             */
/*   Updated: 2025/09/09 16:35:40 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Finish perpendicular distance calculation */
void	finalize_dist(t_game *g, t_ray *r)
{
	if (r->side == 0)
		r->perp_dist = (r->map_x - g->player.x
				+ (1 - r->step_x) / 2.0) / r->ray_dir_x;
	else
		r->perp_dist = (r->map_y - g->player.y
				+ (1 - r->step_y) / 2.0) / r->ray_dir_y;
}

/* Calculate vertical slice start/end and height */
void	calc_slice(t_game *g, t_ray *r, t_slice_info *s)
{
	int	h;

	h = g->win_h;
	s->hgt = (int)(h / r->perp_dist);
	s->start = -(s->hgt) / 2 + h / 2;
	if (s->start < 0)
		s->start = 0;
	s->end = (s->hgt) / 2 + h / 2;
	if (s->end >= h)
		s->end = h - 1;
}

/* Compute exact wall hit x-coordinate for texture mapping */
double	compute_wall_x(t_game *g, t_ray *r)
{
	double	wall_x;

	if (r->side == 0)
		wall_x = g->player.y + r->perp_dist * r->ray_dir_y;
	else
		wall_x = g->player.x + r->perp_dist * r->ray_dir_x;
	return (wall_x - floor(wall_x));
}

/* Draw the textured vertical slice */
void	draw_vertical_line(t_game *g, t_ray *r, t_slice_info *s, int x)
{
	int	y;
	int	ty;
	int	color;

	y = s->start;
	ty = 0;
	color = 0;
	while (y <= s->end)
	{
		ty = (int)s->pos % s->tex->height;
		color = *(int *)(s->tex->data + ty * s->tex->size_line
				+ s->tex_x * 4);
		if (r->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		*(int *)(g->frame.data + y * g->frame.size_line
				+ x * 4) = color;
		s->pos += s->step;
		y++;
	}
}

/* Draw the textured vertical slice */
void	draw_wall_slice(t_game *g, int x, t_ray *r)
{
	t_slice_info	s;

	s.wall_x = compute_wall_x(g, r);
	s.tex = &g->texture[select_tex(r)];
	s.tex_x = (int)(s.wall_x * s.tex->width);
	calc_slice(g, r, &s);
	if ((r->side == 0 && r->ray_dir_x > 0)
		|| (r->side == 1 && r->ray_dir_y < 0))
		s.tex_x = s.tex->width - s.tex_x - 1;
	s.step = (double)s.tex->height / s.hgt;
	s.pos = (s.start - g->win_h / 2 + s.hgt / 2) * s.step;
	draw_vertical_line(g, r, &s, x);
}
