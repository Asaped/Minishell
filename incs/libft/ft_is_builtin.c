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
	int len;

	len = ft_strlen(str);
	if (!ft_strncmp(str, "echo", len) || !ft_strncmp(str, "cd", len)
		|| !ft_strncmp(str, "pwd", len) || !ft_strncmp(str, "export", len)
		|| !ft_strncmp(str, "unset", len) || !ft_strncmp(str, "env", len)
		|| !ft_strncmp(str, "exit", len))
		return (1);
	return (0);
}