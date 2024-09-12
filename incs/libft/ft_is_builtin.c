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
	char	*tmp;
	int		i;

	if (ft_strlen(str) == 0)
		return (0);
	tmp = ft_strdup(str);
	if (!tmp)
		return (0);
	i = -1;
	while (tmp[++i])
		if (ft_is_upper_case(tmp[i]))
			tmp[i] = ft_tolower(tmp[i]);
	if (!ft_strncmp(tmp, "echo", ft_strlen(tmp)) || !ft_strncmp(tmp, "cd", ft_strlen(tmp))
		|| !ft_strncmp(tmp, "pwd", ft_strlen(tmp)) || !ft_strncmp(tmp, "export", ft_strlen(tmp))
		|| !ft_strncmp(tmp, "unset", ft_strlen(tmp)) || !ft_strncmp(tmp, "env", ft_strlen(tmp))
		|| !ft_strncmp(tmp, "exit", ft_strlen(tmp)))
	{
		free(tmp);
		str = lower_str(str);
		return (1);
	}
	free(tmp);
	return (0);
}