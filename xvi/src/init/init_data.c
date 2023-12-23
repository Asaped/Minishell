/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:04:02 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:54:15 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	init_venv(t_data *data, char **env)
{
	int	i;

	i = -1;
	data->env = ft_calloc(venv_count(env) + 1, sizeof * data->env);
	if (!data->env)
		return (false);
	while (env[++i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
			return (false);
	}
	return (true);
}

static bool	init_wds(t_data *data)
{
	char	str[PATH_MAX];
	char	*wd;

	wd = getcwd(str, PATH_MAX);
	data->wdir = ft_strdup(wd);
	if (!data->wdir)
		return (false);
	if (venv_index(data->env, "OLDPWD") != -1)
	{
		data->old_wdir = ft_strdup(venv_value(data->env, "OLDPWD"));
		if (!data->old_wdir)
			return (false);
	}
	else
	{
		data->old_wdir = ft_strdup(wd);
		if (!data->old_wdir)
			return (false);
	}
	return (true);
}

void	init_io(t_cmd *cmd)
{
	if (!cmd->io_fds)
	{
		cmd->io_fds = malloc(sizeof * cmd->io_fds);
		if (!cmd->io_fds)
			return ;
		cmd->io_fds->infile = NULL;
		cmd->io_fds->outfile = NULL;
		cmd->io_fds->hdc_delimiter = NULL;
		cmd->io_fds->hdc_quotes = false;
		cmd->io_fds->fd_in = -1;
		cmd->io_fds->fd_out = -1;
		cmd->io_fds->stdin_copy = -1;
		cmd->io_fds->stdout_copy = -1;
	}
}

bool	init_data(t_data *data, char **env)
{
	if (!init_venv(data, env))
	{
		errmsg_cmd("Fatal", NULL, "Environnement non accessible.", 1);
		return (false);
	}
	if (!init_wds(data))
	{
		errmsg_cmd("Fatal", NULL, "Working directory non accessible.", 1);
		return (false);
	}
	data->token = NULL;
	data->user_input = NULL;
	data->cmd = NULL;
	data->pid = -1;
	g_exit_status = 0;
	return (true);
}
