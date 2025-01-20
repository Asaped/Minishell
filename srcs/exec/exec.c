/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:45:17 by nigateau          #+#    #+#             */
/*   Updated: 2025/01/20 20:44:41 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

// Gestion des pipes pour une commande donnée
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
		{
			g_exit_status = errno;
			exit(EXIT_FAILURE);
		}
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		{
			perror("Error with dup2");
			g_exit_status = errno;
			exit(EXIT_FAILURE);
		}
		close(cmd->fd_in);
	}
	if (cmd->output)
	{
		if (cmd->fd_out == -1)
		{
			g_exit_status = errno;
			exit(EXIT_FAILURE);
		}
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		{
			perror("Error with dup2");
			g_exit_status = errno;
			exit(EXIT_FAILURE);
		}
		close(cmd->fd_out);
	}
}

// Exécution d'une commande
void	execute_command(t_cmd *cmd, char **env)
{
	if (!ft_strncmp(cmd->token[0], "..", 3))
	{
		fprintf(stderr, "bash: line 1: %s: Command not found\n", cmd->token[0]);
		g_exit_status = 127;
		exit(g_exit_status);
	}
	else if (!ft_strncmp(cmd->token[0], ".", 2))
	{
		fprintf(stderr, "bash: line 1: %s: filename argument required\n.: usage: . filename [arguments]\n",
			cmd->token[0]);
		g_exit_status = 2;
		exit(g_exit_status);
	}
	else if (ft_strchr(cmd->token[0], '/') != NULL && !cmd->path_bin)
	{
		g_exit_status = 127;
		fprintf(stderr, "bash: %s: No such file or directory\n", cmd->token[0]);
		exit(g_exit_status);
	}
	else if (!cmd->path_bin)
	{
		fprintf(stderr, "bash: %s: Command not found\n", cmd->token[0]);
		g_exit_status = 127;
		exit(g_exit_status);
	}
	else if (ft_strchr(cmd->token[0], '/') != NULL && cmd->path_bin)
	{
		if (ft_is_dir(cmd->path_bin) == 1)
		{
			g_exit_status = 126;
			fprintf(stderr, "bash: %s: Is a directory\n", cmd->token[0]);
			exit(g_exit_status);
		}
		else if (access(cmd->path_bin, X_OK) == -1)
		{
			g_exit_status = 126;
			fprintf(stderr, "bash: %s: Permission denied\n", cmd->token[0]);
			exit(g_exit_status);
		}
	}
	if (execve(cmd->path_bin, cmd->token, env) == -1)
	{
		perror(cmd->token[0]);
		g_exit_status = errno;
	}
	exit(g_exit_status);
}

// Fork et exécution d'une commande
void	fork_and_execute(t_mini *shell, t_cmd *cmd, int prev_fd,
		int is_last_cmd)
{
	shell->pid = fork();
	if (shell->pid == -1)
	{
		perror("Error with fork");
		g_exit_status = errno;
		exit(EXIT_FAILURE);
	}
	if (shell->pid == 0)
	{
		setup_pipes(cmd, prev_fd, is_last_cmd);
		setup_redirections(cmd);
		execute_command(cmd, shell->env);
	}
	else
	{
		if (prev_fd != -1)
			close(prev_fd);
		if (!is_last_cmd)
			close(cmd->fd_pipe[1]);
	}
}

// Pipeline principal
void	execute_pipeline(t_mini *shell)
{
	int		i;
	int		prev_fd;
	int		status;
	t_cmd	*cmd;

	i = 0;
	prev_fd = -1;
	status = 0;
	while (i < shell->clen)
	{
		cmd = &shell->cmd[i];
		if (cmd->token[0] && is_builtin(cmd->token[0]))
		{
			execute_builtin(cmd, shell, &prev_fd, i);
			i++;
			continue ;
		}
		if (i < shell->clen - 1 && pipe(cmd->fd_pipe) == -1)
		{
			perror("Error with pipe");
			g_exit_status = errno;
			exit(EXIT_FAILURE);
		}
		fork_and_execute(shell, cmd, prev_fd, i == shell->clen - 1);
		if (prev_fd != -1)
			close(prev_fd);
		if (i < shell->clen - 1)
		{
			close(cmd->fd_pipe[1]);
			prev_fd = cmd->fd_pipe[0];
		}
		i++;
	}
	while (waitpid(-1, &status, 0) > 0)
		update_exit_status(status);
}
/*void    check_dot(t_cmd *cmd)
{
    struct stat sb;

    if (!ft_strncmp(cmd->token[0], ".", 2) )
    return ;
}*/
