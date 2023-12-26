/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_identifier.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:39:43 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/26 08:59:46 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_valid_char(char c)
{
	if (ft_isalnum(c) == 0 && c != '_')
		return (false);
	else
		return (true);
}

int	venv_len(char *str)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (str[i] != '$')
		i++;
	i++;
	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '?')
		return (count + 1);
	while (str[i])
	{
		if (is_valid_char(str[i]) == false)
			break ;
		count++;
		i++;
	}
	return (count);
}

char	*var_identifier(char *str)
{
	char	*var;
	char	*tmp;
	int		start;
	int		len;
	int		i;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			start = i + 1;
			break ;
		}
		i++;
	}
	len = venv_len(str);
	var = ft_substr(str, start, len);
	if (!var)
		return (NULL);
	tmp = ft_strjoin(var, "=");
	free_ptr(var);
	var = tmp;
	return (var);
}
