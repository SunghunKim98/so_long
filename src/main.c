# include "so_long.h"
# include "get_next_line.h"

void        mk_one_pixel(void *mlx_ptr, void *win_ptr, void *img_ptr, char **p)
{
	t_info	info;

	find_info(&info, p);
	printf("%d %d\n", info.x, info.y);

	for (int i = 0; i < info.y; i++)
	{
		for (int j = 0; j < info.x; j++)
		{
			if (p[i][j] == '0') // empty space
				mlx_put_image_to_window_scale(mlx_ptr, win_ptr, img_ptr, 32, 64, 32, 32, 64 * j, 64 * i, 65, 65, 0x81DAF5);
			else if (p[i][j] == '1') // wall
				mlx_put_image_to_window_scale(mlx_ptr, win_ptr, img_ptr, 32, 64, 32, 32, 64 * j, 64 * i, 65, 65, 0x585858);
			else if (p[i][j] == 'C') // collectible
				mlx_put_image_to_window_scale(mlx_ptr, win_ptr, img_ptr, 32, 64, 32, 32, 64 * j, 64 * i, 65, 65, 0xF5A9F2);
			else if (p[i][j] == 'E') // map exit
				mlx_put_image_to_window_scale(mlx_ptr, win_ptr, img_ptr, 32, 64, 32, 32, 64 * j, 64 * i, 65, 65, 0xFFFF00);
			else if (p[i][j] == 'P') // starting point
				mlx_put_image_to_window_scale(mlx_ptr, win_ptr, img_ptr, 32, 64, 32, 32, 64 * j, 64 * i, 65, 65, 0x0000FF00);
		}
	}
}

int	main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	img;

	void	*img_get;
	int		img_height;
	int		img_width;
	char	**p;
	char	*tmp;

	int		fd;
	t_info	info;

	// that connects you to the Mac's graphical server 
	mlx_ptr = mlx_init();

	img_get = mlx_xpm_file_to_image(mlx_ptr, "../IceTileset.xpm", &img_width, &img_height);
	// mlx_put_image_to_window(mlx_ptr, win_ptr, img_get, 200, 300); //이미지를 윈도우에 올린다.

	// int mlx_put_image_to_window_scale(void *mlx_ptr, void *win_ptr, void *img_ptr, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh, unsigned int color);
	//mlx_put_image_to_window_scale(mlx_ptr, win_ptr, img_get, 32, 64, 32, 32, 0, 0, 1280, 640, 0x2465FE);

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("file");
		exit(1);
	}

	int	i = 0;

	// while ((get_next_line(fd, &tmp)))
	// 	i++;
	// p = (char**)malloc(sizeof(char*) * (i + 1));

	while ((get_next_line(fd, &p[i])))
		i++;
	p[i] = 0;

	find_info(&info, p);
	printf("%d %d\n", info.x, info.y);

	win_ptr = mlx_new_window(mlx_ptr, 64 * info.x, 64 * info.y, "hello world");

	mk_one_pixel(mlx_ptr, win_ptr, img_get, p);



/*
	img.img = mlx_new_image(mlx_ptr, 500, 500);// 이미지 instance 생성
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//이미지의 주소 할당
	for(int i = 0; i < 500 ; i++) {
		my_mlx_pixel_put(&img, i, i, 0x00FF0000);// 붉은색 선을 대각선으로 그린다.
		my_mlx_pixel_put(&img, 5, i, 0x00FF0000);// 붉은색 선을 세로으로 그린다.
		my_mlx_pixel_put(&img, i, 5, 0x00FF0000);// 붉은색 선을 가로으로 그린다.
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);//이미지를 윈도우에 올린다.
*/

	mlx_hook(win_ptr, X_KEY_PRESS, 0, mlx_key_handle, 0);
	mlx_hook(win_ptr, X_BUTTON_RED_CROSS, 0, exit_program, 0);
	mlx_loop(mlx_ptr);
	
}