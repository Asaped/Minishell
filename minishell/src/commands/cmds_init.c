/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:34:52 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:07:39 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	no_arg_cmd(t_data *data)
{
	t_cmd	*cmd;

	if (!data || !data->cmd)
		return ;
	cmd = data->cmd;
	while (cmd && cmd->command)
	{
		if (!cmd->args)
		{
			cmd->args = malloc(sizeof * cmd->args * 2);
			cmd->args[0] = ft_strdup(cmd->command);
			cmd->args[1] = NULL;
		}
		cmd = cmd->next;
	}
	cmd = last_cmd(data->cmd);
}

void	init_commands(t_data *data, t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type == END)
		return ;
	while (tmp->next)
	{
		if (tmp == token)
			add_cmd(&data->cmd, create_cmd(false));
		if (tmp->type == WORD || tmp->type == VAR)
			parse_word(&data->cmd, &tmp);
		else if (tmp->type == REDIR_OUT)
			parse_redirout(&data->cmd, &tmp);
		else if (tmp->type == REDIR_IN)
			parse_redirin(&data->cmd, &tmp);
		else if (tmp->type == HEREDOC)
			parse_heredoc(data, &data->cmd, &tmp);
		else if (tmp->type == APPEND)
			parse_append(&data->cmd, &tmp);
		else if (tmp->type == PIPE)
			parse_pipe(&data->cmd, &tmp);
		else if (tmp->type == END)
			break ;
	}
	no_arg_cmd(data);
}
