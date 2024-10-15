/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moturki <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:19:13 by moturki           #+#    #+#             */
/*   Updated: 2023/10/23 15:57:48 by moturki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*worddup(const char *s, int i, int n)
{
	int		j;
	char	*str;

	j = 0;
	if (is_quote(s[i]))
	{
		i++;
		n -= 2;
	}
	str = malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	while (j < n)
	{
		str[j] = s[i + j];
		j++;
	}
	str[j] = 0;
	return (str);
}