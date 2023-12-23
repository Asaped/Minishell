/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:07:35 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:07:30 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_cmd(t_cmd *cmd, void (*del)(void *))
{
	if (cmd->command)
		(*del)(cmd->command);
	if (cmd->args)
		free_tab(cmd->args);
	if (cmd->pipe_fd)
		(*del)(cmd->pipe_fd);
	if (cmd->io_fds)
		free_io(cmd->io_fds);
	(*del)(cmd);
}

void	free_cmdlst(t_cmd **cmds, void (*del)(void *))
{
	t_cmd	*tmp;

	tmp = NULL;
	while (*cmds)
	{
		tmp = (*cmds)->next;
		free_cmd(*cmds, del);
		*cmds = tmp;
	}
}
