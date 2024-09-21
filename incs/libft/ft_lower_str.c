/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lower_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moturki <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:05:00 by moturki           #+#    #+#             */
/*   Updated: 2023/10/23 11:28:08 by moturki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *lower_str(char *str)
{
    int	i;

    i = -1;
    while (str[++i])
        if (ft_is_upper_case(str[i]))
            str[i] = ft_tolower(str[i]);
    return (str);
}
