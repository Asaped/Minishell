/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 10:19:16 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:06:19 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	create_arg_echo(t_token **token, t_cmd *cmd)
{
	t_token	*tmp;
	int		arg_count;
	int		i;

	remove_empty_args(token);
	tmp = *token;
	arg_count = count_args(tmp);
	cmd->args = malloc(sizeof(char *) * (arg_count + 2));
	if (!cmd->args)
		return (FAILURE);
	i = 0;
	cmd->args[i] = ft_strdup(cmd->command);
	i++;
	while (tmp->type == WORD || tmp->type == VAR)
	{
		if (tmp->join == true)
			cmd->args[i] = var_joiner(&tmp);
		else
			cmd->args[i] = ft_strdup(tmp->str);
		i++;
		tmp = tmp->next;
	}
	cmd->args[i] = NULL;
	*token = tmp;
	return (SUCCESS);
}

int	add_arg_echo(t_token **token, t_cmd *cmd)
{
	char	**tab;
	t_token	*tmp;
	int		len;
	int		arg_count;

	remove_empty_args(token);
	tmp = *token;
	arg_count = count_args(tmp);
	len = 0;
	while (cmd->args[len])
		len++;
	tab = malloc(sizeof(char *) * (len + arg_count + 1));
	if (!tab)
		return (FAILURE);
	tab = add_args_echo_tab(len, tab, cmd, tmp);
	free(cmd->args);
	cmd->args = tab;
	while (tmp->type == WORD || tmp->type == VAR)
		tmp = tmp->next;
	*token = tmp;
	return (SUCCESS);
}
