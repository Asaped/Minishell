/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:57:20 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:41:40 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Prépare les commandes sans argument
static void	prep_no_arg_cmds(t_data *data)
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

// Crée une liste de commandes à partir des tokens
// Parcourt la liste de tokens et crée des commandes en fonction du type
// Gère différents types de commandes et leurs paramètres spécifiques
// À la fin, appelle `prep_no_arg_cmds` pour préparer les commandes sans args
void	create_commands(t_data *data, t_token *token)
{
	t_token	*temp;

	temp = token;
	if (temp->type == END)
		return ;
	while (temp->next != NULL)
	{
		if (temp == token)
			cmd_adder(&data->cmd, cmd_creator(false));
		if (temp->type == WORD || temp->type == VAR)
			parse_word(&data->cmd, &temp);
		else if (temp->type == INPUT)
			parse_input(&data->cmd, &temp);
		else if (temp->type == TRUNC)
			parse_trunc(&data->cmd, &temp);
		else if (temp->type == HEREDOC)
			parse_heredoc(data, &data->cmd, &temp);
		else if (temp->type == APPEND)
			parse_append(&data->cmd, &temp);
		else if (temp->type == PIPE)
			parse_pipe(&data->cmd, &temp);
		else if (temp->type == END)
			break ;
	}
	prep_no_arg_cmds(data);
}
