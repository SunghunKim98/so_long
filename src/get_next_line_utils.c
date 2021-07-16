/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungkim <sungkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:27:29 by sungkim           #+#    #+#             */
/*   Updated: 2021/06/30 21:39:22 by sungkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen_g(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_g(char *dest, char *src)
{
	int		n1;
	int		n2;
	char	*p;
	int		i;

	if (dest == 0 && src == 0)
		return (NULL);
	n1 = ft_strlen_g(dest);
	n2 = ft_strlen_g(src);
	p = (char*)malloc(sizeof(char) * (n1 + n2 + 1));
	if (p == NULL)
		return (NULL);
	i = -1;
	while (++i < n1)
		p[i] = dest[i];
	i = 0;
	while (i < n2)
	{
		p[n1 + i] = src[i];
		i++;
	}
	p[n1 + i] = '\0';
	free(dest);
	return (p);
}

void	ft_strlcpy_g(char *dest, char *src, int dstsize)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (src[size])
		size++;
	if (dstsize == 0)
		return ;
	while (i < dstsize - 1 && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
