/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moturki <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:36:05 by moturki           #+#    #+#             */
/*   Updated: 2023/10/31 12:48:31 by moturki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list5
{
	int		fd;
	int		curlen;
	int		size;
	char	buffer[BUFFER_SIZE];
}				t_list5;

char	*get_next_line(int fd);

int		ft_strlen2(const char *str);

char	*ft_strjoin2(char *s1, char s2);

int		init_info(t_list5 *info, int fd);

char	set_char(t_list5 *info);

#endif
