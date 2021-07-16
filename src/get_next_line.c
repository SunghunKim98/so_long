/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungkim <sungkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:01:52 by sungkim           #+#    #+#             */
/*   Updated: 2021/06/30 21:41:39 by sungkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		check_g(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*extract_line(char *str)
{
	int		size;
	char	*p;

	size = 0;
	while (str[size] != '\n' && str[size])
		size++;
	p = (char*)malloc(sizeof(char) * (size + 1));
	ft_strlcpy_g(p, str, size + 1);
	return (p);
}

char	*extract_remainder(char *str)
{
	int		size;
	int		total_size;
	char	*p;

	size = 0;
	while (str[size] != '\n' && str[size])
		size++;
	if (!str[size])
	{
		free(str);
		return (0);
	}
	total_size = ft_strlen_g(str);
	if (size == total_size && str[size] != 0)
	{
		p = (char*)malloc(sizeof(char) * (size + 1));
		ft_strlcpy_g(p, str, size + 1);
		free(str);
		return (p);
	}
	p = (char*)malloc(sizeof(char) * (total_size - size + 1));
	ft_strlcpy_g(p, str + size + 1, total_size - size + 2);
	free(str);
	return (p);
}

int		get_next_line(int fd, char **line)
{
	char		buff[BUFFER_SIZE + 1];
	static char	*remainder;
	int			result_read;
	int			result_check;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	result_read = 1;
	while ((result_check = check_g(remainder)) == 0 && result_read > 0)
	{
		if ((result_read = read(fd, buff, BUFFER_SIZE)) < 0)
			return (-1);
		buff[result_read] = '\0';
		if (result_read == 0)
		{
			remainder = ft_strjoin_g(remainder, buff);
			*line = extract_line(remainder);
			remainder = extract_remainder(remainder);
			return (0);
		}
		remainder = ft_strjoin_g(remainder, buff);
	}
	*line = extract_line(remainder);
	remainder = extract_remainder(remainder);
	return (1);
}
