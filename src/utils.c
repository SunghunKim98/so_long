#include "so_long.h"

int	exit_program(void)
{
	exit(0);
	return (0);
}

int	mlx_key_handle(int keycode)
{
	printf("keycode : %d\n", keycode);
	if (keycode == 53)
		return (exit_program());
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8)); // ?? 나누기 8의 정체는?
	*(unsigned int*)dst = color;
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