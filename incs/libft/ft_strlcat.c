/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moturki <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:11:41 by moturki           #+#    #+#             */
/*   Updated: 2023/10/24 01:10:58 by moturki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dst_size;
	size_t	src_size;

	dst_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	i = 0;
	j = 0;
	if (size <= dst_size)
		return (size + src_size);
	while (dst_size + i < size - 1 && src[j] && size != 0)
		dst[dst_size + i++] = src[j++];
	if (dst_size + i < size)
		dst[dst_size + i] = 0;
	return (dst_size + src_size);
}
