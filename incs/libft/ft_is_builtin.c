/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtin.c                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: moturki <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:57:57 by moturki           #+#    #+#             */
/*   Updated: 2023/10/23 11:00:25 by moturki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_builtin(char *str)
{
	if (!ft_strncmp(str, "echo", ft_strlen(str)) || !ft_strncmp(str, "cd", ft_strlen(str))
		|| !ft_strncmp(str, "pwd", ft_strlen(str)) || !ft_strncmp(str, "export", ft_strlen(str))
		|| !ft_strncmp(str, "unset", ft_strlen(str)) || !ft_strncmp(str, "env", ft_strlen(str))
		|| !ft_strncmp(str, "exit", ft_strlen(str)))
		return (1);
	return (0);
}