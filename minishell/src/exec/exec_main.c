/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:38:17 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/26 09:32:21 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_exit_status;

static int	get_child(t_data *data)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	close_fds(data->cmd, false);
	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == data->pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

static int	create_child(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	while (data->pid != 0 && cmd)
	{
		data->pid = fork();
		if (data->pid == -1)
			return (errmsg_cmd("fork", NULL, strerror(errno), EXIT_FAILURE));
		else if (data->pid == 0)
			execute_command(data, cmd);
		cmd = cmd->next;
	}
	return (get_child(data));
}

static int	exec_prep(t_data *data)
{
	if (!data || !data->cmd)
		return (EXIT_SUCCESS);
	if (!data->cmd->command)
	{
		if (data->cmd->io_fds
			&& !check_if_of(data->cmd->io_fds))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(data))
		return (EXIT_FAILURE);
	return (CMD_NOT_FOUND);
}

int	execute(t_data *data)
{
	int	ret;

	ret = exec_prep(data);
	if (ret != CMD_NOT_FOUND)
		return (ret);
	if (!data->cmd->pipe_output && !data->cmd->prev
		&& check_if_of(data->cmd->io_fds))
	{
		io_redirecter(data->cmd->io_fds);
		ret = execute_builtin(data, data->cmd);
		io_restorer(data->cmd->io_fds);
	}
	if (ret != CMD_NOT_FOUND)
		return (ret);
	return (create_child(data));
}
