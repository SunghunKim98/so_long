# include "so_long.h"

static int  give_me_num(long long n)
{
	int num;

	num = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		num++;
	}
	return (num);
}

static int  give_div_num(int n)
{
	int i;
	int sum;

	i = 0;
	sum = 1;
	while (i < n - 1)
	{
		sum = 10 * sum;
		i++;
	}
	return (sum);
}

void        set_flag(int n, int *flag, long long *num)
{
	if (n < 0)
	{
		*flag = 1;
		*num = -(*num);
	}
	else
		*flag = 0;
}

char        *ft_itoa(int n)
{
	char		*p;
	int			i;
	int			digit;
	int			flag;
	long long	num;

	num = (long long)n;
	set_flag(n, &flag, &num);
	digit = give_me_num(num);
	p = (char*)malloc(sizeof(char) * (digit + 1 + flag));
	if (p == 0)
		return (NULL);
	i = -1;
	p[0] = '-';
	while (++i < digit)
	{
		p[i + flag] = num / give_div_num(digit - i) + '0';
		num = num % give_div_num(digit - i);
	}
	p[i + flag] = '\0';
	return (p);
}