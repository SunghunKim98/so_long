#ifndef SO_LONG_H
#define SO_LONG_H

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

# define X_KEY_PRESS 2
# define X_KEY_RELEASE 3
# define X_BUTTON_RED_CROSS 17
# define X_BUTTON_LEFT 123
# define X_BUTTON_RIGHT 124
# define X_BUTTON_DOWN 125
# define X_BUTTON_UP 126

typedef	struct	s_info{
	int		x;
	int		y;
}				t_info;

typedef	struct	s_location{
	int		x;
	int		y;
}				t_location;

typedef	struct	s_img{
	int		width;
	int		height;
}				t_img;

typedef	struct	s_important
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	t_location	loc_character;
	t_img		img;
	char		**p;
	int			count;
	int			num_exit;
	int			num_start;
	int			num_collectibles;
	int			get_collectibles;
}				t_important;

void		raises_collectible(void *mlx_ptr, void *win_ptr, int x, int y);
void		raises_character(void *mlx_ptr, void *win_ptr, int x, int y);
void        create_map(t_important *all);


int		exit_program(void);
void	create_map_2(t_important *all);
int		move_left(t_important *all);
int		mlx_key_handle(int keycode, void *param);
int		mlx_put_image_to_window_scale(void *mlx_ptr, void *win_ptr, void *img_ptr, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh, unsigned int color);
void	find_info(t_info *info, char **p);


void	deal_error(char *str);
int		ft_strlen(char *str);


char        *ft_itoa(int n);

#endif