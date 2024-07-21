/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_file.c                                        :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: moturki <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:00:45 by moturki           #+#    #+#             */
/*   Updated: 2023/10/23 11:00:48 by moturki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_file(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	while (len >= 0 && str[len] != '.' && ft_isalpha(str[len]))
		len--;
	if (str[len] == '.')
		return (1);
	return (0);
}