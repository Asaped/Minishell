/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:32:01 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 12:01:34 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Realloc pour ajouter ou supprimer les venv
static char	**venv_realloc(t_data *data, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof * new_env);
	if (!new_env)
		return (NULL);
	i = 0;
	while (data->env[i] && i < size)
	{
		new_env[i] = ft_strdup(data->env[i]);
		free_ptr(data->env[i]);
		i++;
	}
	free(data->env);
	return (new_env);
}

// Ajoute a la fin ou met a jour une venv
bool	venv_set(t_data *data, char *key, char *value)
{
	int		position;
	char	*tmp;

	position = venv_index(data->env, key);
	if (value == NULL)
		value = "";
	tmp = ft_strjoin("=", value);
	if (!tmp)
		return (false);
	if (position != -1 && data->env[position])
	{
		free_ptr(data->env[position]);
		data->env[position] = ft_strjoin(key, tmp);
	}
	else
	{
		position = venv_count(data->env);
		data->env = venv_realloc(data, position + 1);
		if (!data->env)
			return (false);
		data->env[position] = ft_strjoin(key, tmp);
	}
	free_ptr(tmp);
	return (true);
}

// Supprime la venv a un endroit donné, et libère les ressources
bool	venv_delete(t_data *data, int position)
{
	int	i;
	int	count;

	if (position > venv_count(data->env))
		return (false);
	free_ptr(data->env[position]);
	i = position;
	count = position;
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
