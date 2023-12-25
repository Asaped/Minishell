/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:34:54 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/25 15:25:08 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	increment_shlvl(t_data *data)
{
	char	*tmp;
	int		swap;

	tmp = venv_value(data->env, "SHLVL");
	if (!tmp)
		tmp = ft_strdup("1");
	swap = ft_atoi(tmp) + 1;
	tmp = ft_itoa(swap);
	venv_set(data, "SHLVL", tmp);
	free(tmp);
	return ;
}

static bool	init_env(t_data *data, char **env)
{
	int		i;

	data->env = ft_calloc(env_var_count(env) + 1, sizeof * data->env);
	if (!data->env)
		return (false);
	i = -1;
	while (env[++i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
			return (false);
	}
	increment_shlvl(data);
	return (true);
}

static bool	init_wds(t_data *data)
{
	char	buff[PATH_MAX];
	char	*wd;

	wd = getcwd(buff, PATH_MAX);
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

bool	init_data(t_data *data, char **env)
{
	if (!init_env(data, env))
	{
		errmsg_cmd("Fatal", NULL, "Could not initialize environment", 1);
		return (false);
	}
	if (!init_wds(data))
	{
		errmsg_cmd("Fatal", NULL, "Could'nt initialize working directories", 1);
		return (false);
	}
	data->token = NULL;
	data->user_input = NULL;
	data->cmd = NULL;
	data->pid = -1;
	g_exit_status = 0;
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
