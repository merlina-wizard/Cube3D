#ifndef RENDER_H
#define RENDER_H

typedef struct s_img {
	void *img_ptr; // puntatore all'immagine
	int width; // larghezza dell'immagine
	int height; // altezza dell'immagine
	int endian; // endianess (0 per little-endian, 1 per big-endian)
	char *data; // dati dell'immagine
	int bpp; // byte per pixel
	int size_line; // dimensione della riga in byte
} t_img;

typedef enum e_tex_dir
{
	TEX_NO = 0,
	TEX_SO = 1,
	TEX_WE = 2,
	TEX_EA = 3

}	t_tex_dir;

#endif
