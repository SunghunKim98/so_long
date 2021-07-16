#ifndef SO_LONG_H
#define SO_LONG_H

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

# define X_KEY_PRESS 2
# define X_KEY_RELEASE 3
# define X_BUTTON_RED_CROSS 17

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef	struct	s_info{
	int		x;
	int		y;
}				t_info;

int	    exit_program(void);
int 	mlx_key_handle(int keycode);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int     mlx_put_image_to_window_scale(void *mlx_ptr, void *win_ptr, void *img_ptr, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh, unsigned int color);
void	find_info(t_info *info, char **p);


#endif