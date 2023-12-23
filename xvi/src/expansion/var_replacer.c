/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_replacer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:37:58 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:06:43 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	var_erase(t_token **tokens, char *str, int index)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	i = 0;
	j = 0;
	len = ft_strlen(str) - var_len(str + index);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (1);
	while (str[i])
	{
		if (str[i] == '$' && i == index)
		{
			i += var_len(str + index) + 1;
			if (str[i] == '\0')
				break ;
		}
		result[j++] = str[i++];
	}
	result[j] = '\0';
	free_ptr((*tokens)->str);
	(*tokens)->str = result;
	return (0);
}

static char	*erase_replace(t_token **tokens, char *str, char *var, int index)
{
	char	*result;
	int		len;

	len = ((ft_strlen(str) - var_len(str + index)) + ft_strlen(var));
	result = set_token_str(str, var, len, index);
	if (tokens && *tokens)
	{
		free_ptr((*tokens)->str);
		(*tokens)->str = result;
	}
	return (result);
}

int	var_replace(t_token **tokens, char *var, int i)
{
	if (!var)
	{
		if (var_erase(tokens, (*tokens)->str, i) == 1)
		{
			free_ptr(var);
			return (1);
		}
	}
	else
	{
		if (!erase_replace(tokens, (*tokens)->str, var, i))
		{
			free_ptr(var);
			return (1);
		}
	}
	free_ptr(var);
	return (0);
}

char	*var_replace_hdc(char *str, char *var, int i)
{
	char	*tmp;

	tmp = NULL;
	if (var == NULL)
		*str = '\0';
	else
	{
		tmp = str;
		str = erase_replace(NULL, str, var, i);
		free_ptr(tmp);
	}
	free_ptr(var);
	return (str);
}
