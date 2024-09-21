/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moturki <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:06:50 by moturki           #+#    #+#             */
/*   Updated: 2023/10/23 11:06:52 by moturki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tablen(char **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

char	**ft_tabdup(char **src)
{
	char	**dest;
	int		i;
	int		count;

	i = 0;
	count = ft_tablen(src);
	dest = malloc(sizeof(char *) * count);
	if (!dest)
		return (NULL);
	while (i < count)
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
			return (NULL);
		i++;
	}
	return (dest);
}