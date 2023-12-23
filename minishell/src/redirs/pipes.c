/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:50:13 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:04:49 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_pipe_fds(t_cmd *cmds, t_cmd *to_skip)
{
	while (cmds)
	{
		if (cmds != to_skip && cmds->pipe_fd)
		{
			close(cmds->pipe_fd[0]);
			close(cmds->pipe_fd[1]);
		}
		cmds = cmds->next;
	}
}

bool	create_pipes(t_data *data)
{
	t_cmd	*tmp;
	int		*fd;

	tmp = data->cmd;
	while (tmp)
	{
		if (tmp->pipe_output || (tmp->prev && tmp->prev->pipe_output))
		{
			fd = malloc(sizeof * fd * 2);
			if (!fd || pipe(fd) != 0)
			{
				free_data(data, false);
				return (false);
			}
			tmp->pipe_fd = fd;
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	set_pipe_fds(t_cmd *cmds, t_cmd *cmd)
{
	if (!cmd)
		return (false);
	if (cmd->prev && cmd->prev->pipe_output)
		dup2(cmd->prev->pipe_fd[0], STDIN_FILENO);
	if (cmd->pipe_output)
		dup2(cmd->pipe_fd[1], STDOUT_FILENO);
	close_pipe_fds(cmds, cmd);
	return (true);
}
