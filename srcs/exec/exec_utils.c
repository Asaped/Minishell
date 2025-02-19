/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.lausanne>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:45:17 by nigateau          #+#    #+#             */
/*   Updated: 2025/02/16 22:19:39 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	check_command2(t_cmd *cmd)
{
	if (!cmd->path_bin)
	{
		f_printf(STDERR_FILENO, "bash: ", cmd->token[0], ": Command not found");
		g_exit_status = 127;
		exit(g_exit_status);
	}
	else if (ft_strchr(cmd->token[0], '/') != NULL && cmd->path_bin)
	{
		if (ft_is_dir(cmd->path_bin) == 1)
		{
			g_exit_status = 126;
			f_printf(STDERR_FILENO, "bash: ", cmd->token[0],
				" : Is a directory\n");
			exit(g_exit_status);
		}
		else if (access(cmd->path_bin, X_OK) == -1)
		{
			g_exit_status = 126;
			f_printf(STDERR_FILENO, "bash: ", cmd->token[0],
				": Permission denied");
			exit(g_exit_status);
		}
	}
}

int	check_builtin(t_mini *shell, t_cmd *cmd, int *prev_fd, int *i)
{
	if (cmd->token[0] && is_builtin(cmd->token[0]))
	{
		if (shell->clen == 1)
		{
			execute_builtin(cmd, shell, prev_fd, *i);
			(*i)++;
			return (0);
		}
	}
	if (*i < shell->clen - 1 && pipe(cmd->fd_pipe) == -1)
	{
		perror("Error with pipe");
		g_exit_status = errno;
		exit(EXIT_FAILURE);
	}
	return (1);
}

void	handle_child(t_mini *shell, t_cmd *cmd, int prev_fd, int is_last_cmd)
{
	struct sigaction	restore;

	restore.sa_handler = SIG_DFL;
	sigemptyset(&restore.sa_mask);
	restore.sa_flags = 0;
	sigaction(SIGINT, &restore, NULL);
	setup_pipes(cmd, prev_fd, is_last_cmd);
	setup_redirections(cmd);
	if (is_builtin(cmd->token[0]))
		exit(exec_builtin(cmd, shell));
	execute_command(cmd, shell->env);
}

void	handle_parent(t_cmd *cmd, int prev_fd, int is_last_cmd)
{
	struct sigaction	restore;
	int					status;

	status = 0;
	if (prev_fd != -1)
		close(prev_fd);
	if (!is_last_cmd)
		close(cmd->fd_pipe[1]);
	while (waitpid(-1, &status, 0) > 0)
		update_exit_status(status);
	sigaction(SIGINT, &restore, NULL);
}

void	check_command(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->token[0], "..", 3))
	{
		f_printf(STDERR_FILENO, "bash: line 1: ",
			cmd->token[0], ": Command not found");
		g_exit_status = 127;
		exit(g_exit_status);
	}
	else if (!ft_strncmp(cmd->token[0], ".", 2))
	{
		f_printf(STDERR_FILENO, "bash: ",
			cmd->token[0], ": filename argument needed");
		g_exit_status = 2;
		exit(g_exit_status);
	}
	else if (ft_strchr(cmd->token[0], '/') != NULL && !cmd->path_bin)
	{
		g_exit_status = 127;
		f_printf(STDERR_FILENO, "bash: ",
			cmd->token[0], ": No such file or directory");
		exit(g_exit_status);
	}
}
