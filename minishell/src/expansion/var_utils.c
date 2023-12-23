/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:57:35 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:53:41 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	var_copy(char *result, char *var, int *k)
{
	int	i;

	i = 0;
	while (var[i])
		result[(*k)++] = var[i++];
	return ;
}

int	var_len(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '$')
		i++;
	i++;
	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '?')
		return (++count);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
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

	i = -1;
	start = 0;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			start = i + 1;
			break ;
		}
	}
	len = var_len(str);
	var = ft_substr(str, start, len);
	if (!var)
		return (NULL);
	tmp = ft_strjoin(var, "=");
	free_ptr(var);
	var = tmp;
	return (var);
}

char	*set_token_str(char *old, char *var, int len, int index)
{
	char	*result;
	int		i;
	int		k;

	i = -1;
	k = 0;
	result = malloc(sizeof(char) * len);
	if (!result)
		return (NULL);
	while (old[++i])
	{
		if (old[i] == '$' && i == index)
		{
			var_copy(result, var, &k);
			i += var_len(old + index) + 1;
			if (old[i] == '\0')
				break ;
		}
		result[k++] = old[i++];
	}
	result[k] = '\0';
	return (result);
}
