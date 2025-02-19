/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.lausanne>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:45:17 by nigateau          #+#    #+#             */
/*   Updated: 2025/02/16 22:19:03 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	setup_pipes(t_cmd *cmd, int prev_fd, int is_last_cmd)
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			g_exit_status = errno;
			exit(EXIT_FAILURE);
		}
		close(prev_fd);
	}
	if (!is_last_cmd)
	{
		if (dup2(cmd->fd_pipe[1], STDOUT_FILENO) == -1)
		{
			perror("Error with dup2");
			g_exit_status = errno;
			exit(EXIT_FAILURE);
		}
		close(cmd->fd_pipe[1]);
	}
	close(cmd->fd_pipe[0]);
}

void	setup_redirections(t_cmd *cmd)
{
	if (cmd->input)
	{
		if (cmd->fd_in == -1)
			g_exit_status = errno;
		else if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			g_exit_status = errno;
		if (cmd->fd_in == -1 || dup2(cmd->fd_in, STDIN_FILENO) == -1)
		{
			close(cmd->fd_in);
			exit(EXIT_FAILURE);
		}
		close(cmd->fd_in);
	}
	if (cmd->output)
	{
		if (cmd->fd_out == -1)
			g_exit_status = errno;
		else if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			g_exit_status = errno;
		if (cmd->fd_out == -1 || dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(cmd->fd_out);
	}
}

void	execute_command(t_cmd *cmd, char **env)
{
	check_command(cmd);
	check_command2(cmd);
	if (execve(cmd->path_bin, cmd->token, env) == -1)
	{
		perror(cmd->token[0]);
		g_exit_status = errno;
	}
	exit(g_exit_status);
}

void	fork_and_execute(t_mini *shell, t_cmd *cmd, int prev_fd,
		int is_last_cmd)
{
	struct sigaction	ignore;

	ignore.sa_handler = SIG_IGN;
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;
	sigaction(SIGINT, &ignore, NULL);
	shell->pid = fork();
	if (shell->pid == -1)
	{
		perror("Error with fork");
		g_exit_status = errno;
		exit(EXIT_FAILURE);
	}
	if (shell->pid == 0)
		handle_child(shell, cmd, prev_fd, is_last_cmd);
	else
		handle_parent(cmd, prev_fd, is_last_cmd);
}

void	execute_pipeline(t_mini *shell)
{
	int		i;
	int		prev_fd;
	t_cmd	*cmd;

	i = 0;
	prev_fd = -1;
	while (i < shell->clen)
	{
		cmd = &shell->cmd[i];
		if (!check_builtin(shell, cmd, &prev_fd, &i))
			continue ;
		fork_and_execute(shell, cmd, prev_fd, i == shell->clen - 1);
		if (i < shell->clen - 1)
			prev_fd = cmd->fd_pipe[0];
		i++;
	}
}
