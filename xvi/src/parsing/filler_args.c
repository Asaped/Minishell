/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 10:16:47 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:57:02 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	create_arg_def(t_token **token, t_cmd *cmd)
{
	t_token	*tmp;
	int		arg_count;
	int		i;

	tmp = *token;
	arg_count = count_args(tmp);
	i = 0;
	cmd->args = malloc(sizeof(char *) * (arg_count + 2));
	if (!cmd->args)
		return (FAILURE);
	cmd->args[i++] = ft_strdup(cmd->command);
	while (tmp->type == WORD || tmp->type == VAR)
	{
		cmd->args[i++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	cmd->args[i] = NULL;
	*token = tmp;
	return (SUCCESS);
}

char	**add_args_def_tab(int len, char **tab, t_cmd *cmd, t_token **token)
{
	t_token	*tmp;
	int		i;

	tmp = *token;
	i = -1;
	while (++i < len)
		tab[i] = cmd->args[i];
	while (tmp->type == WORD || tmp->type == VAR)
	{
		tab[i++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	add_arg_def(t_token **token, t_cmd *cmd)
{
	char	**tab;
	t_token	*tmp;
	int		i;
	int		len;

	i = 0;
	tmp = *token;
	len = 0;
	while (cmd->args[len])
		len++;
	while (tmp->type == WORD || tmp->type == VAR)
	{
		i++;
		tmp = tmp->next;
	}
	tab = malloc(sizeof(char *) * (i + len + 1));
	if (!tab)
		return (FAILURE);
	tab = add_args_def_tab(len, tab, cmd, token);
	free(cmd->args);
	cmd->args = tab;
	*token = tmp;
	return (SUCCESS);
}

int	fill_args(t_token **token, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->command, "echo"))
	{
		if (!(cmd->args))
			return (create_arg_echo(token, cmd));
		else
			return (add_arg_echo(token, cmd));
	}
	else
	{
		if (cmd && !(cmd->args))
			return (create_arg_def(token, cmd));
		else
			return (add_arg_def(token, cmd));
	}
	return (SUCCESS);
}
