/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:46:00 by nigateau          #+#    #+#             */
/*   Updated: 2025/01/20 20:46:00 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	get_env_index(char **env, char *key)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, key_len) && (env[i][key_len] == '='
			|| !env[i][key_len]))
			return (i);
		i++;
	}
	return (-1);
}

char	**realloc_env(char **env, int len)
{
	int		i;
	char	**res;

	i = -1;
	res = malloc(sizeof(char *) * (len + 1));
	res[len] = NULL;
	if (!res)
		return (NULL);
	while (env[++i] && i < len)
		res[i] = ft_strdup(env[i]);
	free_tab(env);
	return (res);
}

char	**set_env_var(char **env, char *key, char *value)
{
	int		i;
	char	*new_value;

	i = 0;
	i = get_env_index(env, key);
	if (!value)
		value = "";
	new_value = ft_strjoin3("=", value);
	if (i != -1 && env[i])
	{
		free(env[i]);
		env[i] = ft_strjoin4(key, new_value);
	}
	else
	{
		i = ft_tablen(env);
		env = realloc_env(env, i + 1);
		if (!env)
			return (NULL);
		env[i] = ft_strjoin4(key, new_value);
	}
	return (env);
}

char	*get_env_value(t_mini *shell, char *str, int malloc)
{
	int	i;
	int	len;

	i = 0;
	len = ft_tablen(shell->env);
	while (i < len)
	{
		if (shell->env[i][ft_strlen(str)] == '=' && ft_strncmp(shell->env[i],
				str, ft_strlen(str)) == 0)
		{
			len = ft_strlen(str);
			if (malloc == 1)
				free(str);
			return (shell->env[i] + len + 1);
		}
		i++;
	}
	if (malloc == 1)
		free(str);
	return (NULL);
}
