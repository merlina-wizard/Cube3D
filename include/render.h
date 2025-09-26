/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:26:42 by lorenzo           #+#    #+#             */
/*   Updated: 2025/09/26 11:11:05 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# define VORTEX_FRAMES 4
# define VORTEX_SPEED 100

# define MINIMAP_SCALE    10
# define MINIMAP_OFFSET   20
# define MINIMAP_SIZE     200
# define MINIMAP_PLAYER   3

# define C_MINIMAP_WALL       0x444444
# define C_MINIMAP_FLOOR      0x222222
# define C_MINIMAP_PLAYER     0xFF0000
# define C_MINIMAP_BORDER     0xFFFFFF
# define C_MINIMAP_FOV        0xFFFF00


// typedef struct s_vortex
// {
// 	double	x;
// 	double	y;
// 	t_img	frames[4];
// 	int		current_frame;
// 	int		last_update;
// 	int		active;
// }	t_vortex;

typedef struct s_img
{
	void	*img_ptr; // puntatore all'immagine
	int		width; // larghezza dell'immagine
	int		height; // altezza dell'immagine
	int		endian; // endianess (0 per little-endian, 1 per big-endian)
	char	*data; // dati dell'immagine
	int		bpp; // byte per pixel
	int		size_line; // dimensione della riga in byte
}	t_img;

typedef enum e_tex_dir
{
	TEX_NO = 0,
	TEX_SO = 1,
	TEX_WE = 2,
	TEX_EA = 3
}	t_tex_dir;

typedef struct s_slice_info
{
	t_img	*tex;
	int		tex_x;
	int		start;
	int		end;
	int		hgt;
	double	pos;
	double	step;
	double	wall_x;
}	t_slice_info;

typedef struct s_cell_data
{
	int			h;
	int			w;
	t_player	*p;
	int			*p_count;
}	t_cell_data;

#endif