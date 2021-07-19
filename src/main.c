# include "so_long.h"
# include "get_next_line.h"

void		raises_collectible(void *mlx_ptr, void *win_ptr, int x, int y)
{
	void	*img_ptr;
	int		img_width;
	int		img_height;

	img_ptr = mlx_xpm_file_to_image(mlx_ptr, "ItemsInsect.xpm", &img_width, &img_height);
	mlx_put_image_to_window_scale(mlx_ptr, win_ptr, img_ptr, 64, 0, 32, 32, x, y, 64, 64, 0xFFFFFFFF);
}

void		raises_character(void *mlx_ptr, void *win_ptr, int x, int y)
{
	void	*img_ptr;
	int		img_width;
	int		img_height;

	img_ptr = mlx_xpm_file_to_image(mlx_ptr, "character.xpm", &img_width, &img_height);	
	mlx_put_image_to_window_scale(mlx_ptr, win_ptr, img_ptr, 0, 0, 48, 48, x, y, 64, 64, 0xFFFFFFFF);
}

void        create_map(t_important *all)
{
	t_info	info;

	find_info(&info, all->p);

	for (int i = 0; i < info.y; i++)
	{
		for (int j = 0; j < info.x; j++)
		{
			if (all->p[i][j] == '0')
				mlx_put_image_to_window_scale(all->mlx_ptr, all->win_ptr, all->img_ptr, 32, 64, 32, 32, 64 * j, 64 * i, 65, 65, 0x81DAF5);
			else if (all->p[i][j] == '1')
				mlx_put_image_to_window_scale(all->mlx_ptr, all->win_ptr, all->img_ptr, 32, 64, 32, 32, 64 * j, 64 * i, 65, 65, 0x585858);
			else if (all->p[i][j] == 'C')
			{
				mlx_put_image_to_window_scale(all->mlx_ptr, all->win_ptr, all->img_ptr, 32, 64, 32, 32, 64 * j, 64 * i, 65, 65, 0x81DAF5);
				raises_collectible(all->mlx_ptr, all->win_ptr, 64 * j, 64 * i);
				all->num_collectibles++;
			}
			else if (all->p[i][j] == 'E')
			{
				mlx_put_image_to_window_scale(all->mlx_ptr, all->win_ptr, all->img_ptr, 32, 64, 32, 32, 64 * j, 64 * i, 65, 65, 0xFFFF00);
				all->num_exit++;
			}
			else if (all->p[i][j] == 'P')
			{
				all->loc_character.x = 64 * j;
				all->loc_character.y = 64 * i;
				all->num_start++;
				mlx_put_image_to_window_scale(all->mlx_ptr, all->win_ptr, all->img_ptr, 32, 64, 32, 32, 64 * j, 64 * i, 65, 65, 0x81DAF5);
				raises_character(all->mlx_ptr, all->win_ptr, 64 * j, 64 * i);
			}
		}
	}
}

char	**make_and_return_p(char *argv)
{
	int		fd;
	char	*tmp;
	int		i;
	char	**p;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		deal_error("file");
	i = 0;
	while ((get_next_line(fd, &tmp)))
		i++;
	p = (char**)malloc(sizeof(char*) * (i + 1));
	close(fd);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		deal_error("file");
	i = 0;
	while ((get_next_line(fd, &p[i])))
		i++;
	p[i] = 0;
	return (p);
}

void	init_all(t_important *all, t_info info)
{
	all->mlx_ptr = mlx_init();
	all->img_ptr = mlx_xpm_file_to_image(all->mlx_ptr, "IceTileset.xpm", &all->img.width, &all->img.height);
	all->win_ptr = mlx_new_window(all->mlx_ptr, 64 * info.x, 64 * info.y, "hello world");
	all->count = 0;
	all->get_collectibles = 0;
	all->num_collectibles = 0;
	all->num_start = 0;
	all->num_exit = 0;
}

void	map_validation_step_1(t_important *all, t_info info)
{
	int		i;
	int		j;

	i = -1;
	while (++i < info.x)
		if (all->p[0][i] != '1')
			deal_error("ERROR\n");
	i = -1;
	while (++i < info.x)
		if (all->p[info.y - 1][i] != '1')
			deal_error("ERROR\n");
	i = -1;
	while (++i < info.y)
		if (all->p[i][0] != '1')
			deal_error("ERROR\n");
	i = -1;
	while (++i < info.y)
		if (all->p[i][info.x - 1] != '1')
			deal_error("ERROR\n");
}

void	check_if_map_validated(t_important *all, t_info info)
{
	map_validation_step_1(all, info);
	if (all->num_collectibles == 0 || all->num_exit == 0 || all->num_start == 0)
		deal_error("ERROR\n");
}

int	main(int argc, char **argv)
{
	t_important all;
	t_info	info;

	all.p = make_and_return_p(argv[1]);
	find_info(&info, all.p);

	init_all(&all, info);
	create_map(&all);
	check_if_map_validated(&all, info);
	
	//int mlx_loop_hook(void *mlx_ptr, int (*funct_ptr)(), void *param);

	// here's for exit.
	mlx_hook(all.win_ptr, X_KEY_PRESS, 0, mlx_key_handle, &all);
	mlx_hook(all.win_ptr, X_BUTTON_RED_CROSS, 0, exit_program, 0);
	mlx_loop(all.mlx_ptr);
}