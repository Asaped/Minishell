/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   venv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:15:39 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:03:50 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	venv_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

int	venv_index(char **env, char *var)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (-1);
	while (env[++i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free_ptr(tmp);
			return (1);
		}
	}
	free_ptr(tmp);
	return (-1);
}

char	*venv_value(char **env, char *var)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (NULL);
	while (env[++i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free_ptr(tmp);
			return (ft_strchr(env[i], '=') + 1);
		}
	}
	free_ptr(tmp);
	return (NULL);
}

bool	valid_venv_key(char *venv)
{
	int	i;

	i = 0;
	if (!ft_isalpha(venv[i]) && venv[i] != '_')
		return (false);
	i++;
	while (venv[i] && venv[i] != '_')
	{
		if (!ft_isalnum(venv[i]) && venv[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
