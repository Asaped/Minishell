/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_whitespace.c                                   :+:      :+:    :+: */
/*                                                    +:+ +:+        
	+:+     */
/*   By: moturki <marvin@42lausanne.ch>             +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/10/23 11:00:45 by moturki           #+#    #+#             */
/*   Updated: 2023/10/23 11:00:48 by moturki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'
		|| c == '\f')
		return (1);
	return (0);
}

int	is_only_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_whitespace(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
