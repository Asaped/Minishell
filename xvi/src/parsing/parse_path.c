/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:19:10 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 20:00:44 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**parse_venv_path(t_data *data)
{
	char	**result;

	if (venv_index(data->env, "PATH") == -1)
		return (NULL);
	result = ft_split(venv_value(data->env, "PATH"), ':');
	if (!result)
		return (NULL);
	return (result);
}

static char	*parse_cmd_path(char *cmd, char **paths)
{
	char	*result;
	int		i;

	result = NULL;
	i = -1;
	while (paths[++i])
	{
		result = ft_strjoin(paths[i], cmd);
		if (!result)
		{
			errmsg_cmd("malloc", NULL, "mem allocation failed", EXIT_FAILURE);
			return (NULL);
		}
		if (access(result, F_OK | X_OK) == SUCCESS)
			return (result);
		free_ptr(result);
	}
	return (NULL);
}

char	*get_cmd_path(t_data *data, char *name)
{
	char	**env_path;
	char	*cmd_path;
	char	*cmd;

	if (!name)
		return (NULL);
	env_path = parse_venv_path(data);
	if (!env_path)
		return (NULL);
	cmd = ft_strjoin("/", name);
	if (!cmd)
	{
		free_tab(env_path);
		return (NULL);
	}
	cmd_path = parse_cmd_path(cmd, env_path);
	if (!cmd_path)
	{
		free_ptr(cmd);
		free_tab(env_path);
		return (NULL);
	}
	return (cmd_path);
}
