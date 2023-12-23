/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 09:49:35 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:58:36 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	set_value_cmd(t_cmd **cmd)
{
	(*cmd)->command = NULL;
	(*cmd)->path = NULL;
	(*cmd)->args = NULL;
	(*cmd)->pipe_output = false;
	(*cmd)->pipe_fd = 0;
	(*cmd)->prev = NULL;
	(*cmd)->next = NULL;
}

t_cmd	*create_cmd(bool value)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd) * 1);
	if (!new_cmd)
		return (NULL);
	ft_memset(new_cmd, 0, sizeof(t_cmd));
	new_cmd->pipe_output = value;
	set_value_cmd(&new_cmd);
	return (new_cmd);
}

void	add_cmd(t_cmd **cmds, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	tmp = *cmds;
	if (!tmp)
	{
		*cmds = new_cmd;
		return ;
	}
	if (cmds && *cmds && new_cmd)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
		new_cmd->prev = tmp;
	}
}

t_cmd	*last_cmd(t_cmd *cmd)
{
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}
