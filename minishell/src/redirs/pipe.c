/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 13:03:19 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 14:05:24 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Ferme les descripteurs de fichier de tous les pipes, sauf celui spécifié
void	close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd)
{
	while (cmds)
	{
		if (cmds != skip_cmd && cmds->pipe_fd)
		{
			close(cmds->pipe_fd[0]);
			close(cmds->pipe_fd[1]);
		}
		cmds = cmds->next;
	}
}

// Crée des pipes pour chaque cmd nécessitant une communication inter-process
bool	create_pipes(t_data *data)
{
	int		*fd;
	t_cmd	*tmp;

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

// Configure les descripteurs de fichier stdin et stdout pour les pipes
bool	set_pipe_fds(t_cmd *cmds, t_cmd *c)
{
	if (!c)
		return (false);
	if (c->prev && c->prev->pipe_output)
		dup2(c->prev->pipe_fd[0], STDIN_FILENO);
	if (c->pipe_output)
		dup2(c->pipe_fd[1], STDOUT_FILENO);
	close_pipe_fds(cmds, c);
	return (true);
}
