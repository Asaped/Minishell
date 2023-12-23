/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:02:30 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 20:35:03 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_exit_status;

static int	start_exec(t_data *data)
{
	if (!data || !data->cmd)
		return (EXIT_SUCCESS);
	if (!data->cmd->command)
	{
		if (data->cmd->io_fds && !if_of_checker(data->cmd->io_fds))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(data))
		return (EXIT_FAILURE);
	return (NOT_FUND);
}

static int	get_child(t_data *data)
{
	pid_t	wpid;
	int		status;
	int		status_copy;

	close_fds(data->cmd, false);
	status_copy = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == data->pid)
			status_copy = status;
		continue ;
	}
	if (WIFSIGNALED(status_copy))
		status = 128 + WTERMSIG(status_copy);
	else if (WIFEXITED(status_copy))
		status = WEXITSTATUS(status_copy);
	else
		status = status_copy;
	return (status);
}

static int	create_child(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	while (cmd && data->pid != 0)
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

int	execution(t_data *data)
{
	int	status;

	status = start_exec(data);
	if (status != NOT_FUND)
		return (status);
	if (!data->cmd->pipe_output && !data->cmd->prev
		&& if_of_checker(data->cmd->io_fds))
	{
		io_redir(data->cmd->io_fds);
		status = exec_builtin(data, data->cmd);
		io_restore(data->cmd->io_fds);
	}
	if (status != NOT_FUND)
		return (status);
	return (create_child(data));
}
