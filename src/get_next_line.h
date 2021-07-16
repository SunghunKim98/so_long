/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungkim <sungkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:00:15 by sungkim           #+#    #+#             */
/*   Updated: 2021/06/30 21:41:13 by sungkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5000
# endif

int		check_g(char *str);
char	*extract_line(char *str);
char	*extract_remainder(char *str);

int		ft_strlen_g(char *s);
char	*ft_strjoin_g(char *dest, char *src);
void	ft_strlcpy_g(char *dest, char *src, int dstsize);

int		get_next_line(int fd, char **line);

#endif
