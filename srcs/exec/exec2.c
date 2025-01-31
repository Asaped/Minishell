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

void	execute_command2(t_cmd *cmd, char **env)
{
	if (!cmd->path_bin)
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
}

void	execute_pipeline2(t_mini *shell, t_cmd *cmd)
{
	if (cmd->token[0] && is_builtin(cmd->token[0]))
	{
		execute_builtin(cmd, shell, &prev_fd, i++);
		continue ;
	}
	if (i < shell->clen - 1 && pipe(cmd->fd_pipe) == -1)
	{
		perror("Error with pipe");
		g_exit_status = errno;
		exit(EXIT_FAILURE);
	}
}
