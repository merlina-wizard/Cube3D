/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:26:42 by lorenzo           #+#    #+#             */
/*   Updated: 2025/09/02 00:59:18 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

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