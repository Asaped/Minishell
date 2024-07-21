/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moturki <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:04:47 by moturki           #+#    #+#             */
/*   Updated: 2023/10/23 11:04:49 by moturki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_number(int n)
{
	size_t	count;

	count = 1;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n / 10 > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	count;
	size_t	trigger;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	trigger = 0;
	count = count_number(n);
	str = (char *)malloc(sizeof(char) * count + 1);
	if (!str)
		return (NULL);
	str[count] = 0;
	if (n < 0)
	{
		n *= -1;
		trigger = 1;
	}
	while (count-- > 0)
	{
		str[count] = n % 10 + '0';
		n /= 10;
	}
	if (trigger == 1)
		str[0] = '-';
	return (str);
}
