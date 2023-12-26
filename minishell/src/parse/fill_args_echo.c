/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:59:06 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/26 09:22:24 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	create_args_echo(t_token **token_node, t_cmd *last_cmd)
{
	int		nb_args;
	t_token	*temp;
	int		i;

	venv_remove_empty(token_node);
	temp = *token_node;
	nb_args = args_counter(temp);
	last_cmd->args = malloc(sizeof(char *) * (nb_args + 2));
	if (!last_cmd->args)
		return (FAILURE);
	i = 0;
	last_cmd->args[i] = ft_strdup(last_cmd->command);
	i++;
	while (temp->type == WORD || temp->type == VAR)
	{
		if (temp->join == true)
			last_cmd->args[i] = venv_joiner(&temp);
		else
			last_cmd->args[i] = ft_strdup(temp->str);
		i++;
		temp = temp->next;
	}
	last_cmd->args[i] = NULL;
	*token_node = temp;
	return (SUCCESS);
}

int	add_args_echo(t_token **token_node, t_cmd *last_cmd)
{
	int		len;
	int		nb_args;
	char	**new_tab;
	t_token	*temp;

	venv_remove_empty(token_node);
	temp = *token_node;
	nb_args = args_counter(temp);
	len = 0;
	while (last_cmd->args[len])
		len++;
	new_tab = malloc(sizeof(char *) * (nb_args + len + 1));
	if (!new_tab)
		return (FAILURE);
	new_tab = tab_duplicate(len, new_tab, last_cmd, temp);
	free(last_cmd->args);
	last_cmd->args = new_tab;
	while (temp->type == WORD || temp->type == VAR)
		temp = temp->next;
	*token_node = temp;
	return (SUCCESS);
}
