#include "so_long.h"

void	deal_error(char *str)
{
	write(1, str, ft_strlen(str));
	exit(1);
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_count(int count)
{
	char	*str;

	str = ft_itoa(count);
	write(1, "count: ", 8);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

int	exit_program(void)
{
	exit(0);
	return (0);
}

void        create_map_2(t_important *all)
{
	t_info	info;

	find_info(&info, all->p);

	for (int i = 0; i < info.y; i++)
	{
		for (int j = 0; j < info.x; j++)
		{
			if (all->p[i][j] == '0' || all->p[i][j] == 'P')
				mlx_put_image_to_window_scale(all->mlx_ptr, all->win_ptr, all->img_ptr, 32, 64, 32, 32, 64 * j, 64 * i, 65, 65, 0x81DAF5);
			else if (all->p[i][j] == '1') // wall
				mlx_put_image_to_window_scale(all->mlx_ptr, all->win_ptr, all->img_ptr, 32, 64, 32, 32, 64 * j, 64 * i, 65, 65, 0x585858);
			else if (all->p[i][j] == 'C') // collectible
			{
				mlx_put_image_to_window_scale(all->mlx_ptr, all->win_ptr, all->img_ptr, 32, 64, 32, 32, 64 * j, 64 * i, 65, 65, 0x81DAF5);
				raises_collectible(all->mlx_ptr, all->win_ptr, 64 * j, 64 * i);
			}
			else if (all->p[i][j] == 'E') // map exit
				mlx_put_image_to_window_scale(all->mlx_ptr, all->win_ptr, all->img_ptr, 32, 64, 32, 32, 64 * j, 64 * i, 65, 65, 0xFFFF00);
		}
	}
	if (all->p[all->loc_character.y / 64][all->loc_character.x / 64] == 'C')
	{
		all->p[all->loc_character.y / 64][all->loc_character.x / 64] = '0';
		create_map_2(all);
		all->get_collectibles++;
	}
	if (all->p[all->loc_character.y / 64][all->loc_character.x / 64] == 'E')
		if (all->get_collectibles == all->num_collectibles)
			exit(0);
}

int		check_if_block(t_important *all, int add_x, int add_y)
{
	int	x;
	int	y;

	x = (all->loc_character.x + add_x) / 64;
	y = (all->loc_character.y + add_y) / 64;
	if (all->p[y][x] == '1')
		return (1);
	return (0);
}

int		check_if_collectible(t_important *all, int add_x, int add_y)
{
	int	x;
	int	y;

	x = (all->loc_character.x + add_x) / 64;
	y = (all->loc_character.y + add_y) / 64;
	if (all->p[y][x] == 'C')
	{
		all->get_collectibles++;
		return (1);
	}
	return (0);
}

int		move_left(t_important *all)
{
	if (check_if_block(all, -64, 0))
		return (0);
	all->loc_character.x -= 64;
	create_map_2(all);
	raises_character(all->mlx_ptr, all->win_ptr, all->loc_character.x, all->loc_character.y);
	all->count++;
	print_count(all->count);
	return (0);
}

int		move_right(t_important *all)
{
	if (check_if_block(all, 64, 0))
		return (0);
	all->loc_character.x += 64;
	create_map_2(all);
	raises_character(all->mlx_ptr, all->win_ptr, all->loc_character.x, all->loc_character.y);
	all->count++;
	print_count(all->count);
	return (0);
}

int		move_down(t_important *all)
{
	if (check_if_block(all, 0, 64))
		return (0);
	all->loc_character.y += 64;
	create_map_2(all);
	raises_character(all->mlx_ptr, all->win_ptr, all->loc_character.x, all->loc_character.y);
	all->count++;
	print_count(all->count);
	return (0);
}

int		move_up(t_important *all)
{
	if (check_if_block(all, 0, -64))
		return (0);
	all->loc_character.y -= 64;
	create_map_2(all);
	raises_character(all->mlx_ptr, all->win_ptr, all->loc_character.x, all->loc_character.y);
	all->count++;
	print_count(all->count);
	return (0);
}

int	mlx_key_handle(int keycode, void *param)
{
	t_important *all;

	all = (t_important*)param;
	if (keycode == 53)
		return (exit_program());
	else if (keycode == 0)
		return (move_left(all));
	else if (keycode == 2)
		return (move_right(all));
	else if (keycode == 1)
		return (move_down(all));
	else if (keycode == 13)
		return (move_up(all));
	return (0);
}

void		find_info(t_info *info, char **p)
{
	int		x;
	int		y;
	int		i;
	int		j;

	x = 0;
	while (p[0][x])
		x++;
	y = 0;
	while (p[y])
		y++;
	i = -1;
	info->x = x;
	info->y = y;
	while (++i < y)
	{
		j = -1;
		while (p[i][++j])
		{
			if (j > x)
			{
				// error signal -> it's not rectangular
				exit(1);
			}
		}
	}
}
