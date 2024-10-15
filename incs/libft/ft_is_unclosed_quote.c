/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_unclosed_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moturki <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:01:17 by moturki           #+#    #+#             */
/*   Updated: 2023/10/23 11:01:19 by moturki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	is_unclosed_quote(char *str)
{
	int	i;
	int	pos;

	i = -1;
	while (++i < ft_strlen(str))
	{
		pos = -1;
		while (str[i] && !is_quote(str[i]))
			i++;
		if (is_quote(str[i]))
			pos = i++;
		while (str[i] && str[i] != str[pos])
			i++;
		if (pos != -1 && str[i] != str[pos] && is_quote(str[pos]))
			return (TRUE);
	}
	return (FALSE);
}