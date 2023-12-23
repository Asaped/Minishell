/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   venv_setter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 12:56:18 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:04:12 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**venv_realloc(t_data *data, int size)
{
	char	**result;
	int		i;

	i = 0;
	result = ft_calloc(size + 1, sizeof * result);
	if (!result)
		return (NULL);
	while (data->env[i] && i < size)
	{
		result[i] = ft_strdup(data->env[i]);
		free_ptr(data->env[i]);
		i++;
	}
	free(data->env);
	return (result);
}

bool	venv_set(t_data *data, char *key, char *val)
{
	char	*tmp;
	int		i;

	i = venv_index(data->env, key);
	if (!val)
		val = "";
	tmp = ft_strjoin("=", val);
	if (!tmp)
		return (false);
	if (i != -1 && data->env[i])
	{
		free_ptr(data->env[i]);
		data->env[i] = ft_strjoin(key, tmp);
	}
	else
	{
		i = venv_count(data->env);
		data->env = venv_realloc(data, i + 1);
		if (!data->env)
			return (false);
		data->env[i] = ft_strjoin(key, tmp);
	}
	free_ptr(tmp);
	return (true);
}

bool	venv_remover(t_data *data, int index)
{
	int	count;
	int	i;

	if (index > venv_count(data->env))
		return (false);
	free_ptr(data->env[index]);
	i = index;
	count = index;
	while (data->env[i + 1])
	{
		data->env[i] = ft_strdup(data->env[i + 1]);
		free_ptr(data->env[i + 1]);
		count++;
		i++;
	}
	data->env = venv_realloc(data, count);
	if (!data->env)
		return (false);
	return (true);
}
