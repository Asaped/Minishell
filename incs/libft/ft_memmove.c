/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moturki <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:08:10 by moturki           #+#    #+#             */
/*   Updated: 2023/10/23 11:08:16 by moturki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dest2;
	char	*src2;

	if (!dest && !src)
		return (NULL);
	dest2 = (char *)dest;
	src2 = (char *)src;
	if (dest > src)
		while (n-- > 0)
			dest2[n] = src2[n];
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
