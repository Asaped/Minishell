/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_echo_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 10:21:53 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:06:23 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && (tokens->type == WORD || tokens->type == VAR))
	{
		if (tokens->type == VAR && tokens->join == true)
		{
			while (tokens->type == VAR && tokens->join == true)
				tokens = tokens->next;
			count++;
		}
		else
		{
			count++;
			tokens = tokens->next;
		}
	}
	return (count);
}

void	remove_empty_args(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp->type == WORD || tmp->type == VAR)
	{
		if (tmp->type == VAR && tmp->str[0] == '\0' && tmp->exists == false)
		{
			tmp = tmp->next;
			if (tmp == (*tokens)->next)
				(*tokens) = (*tokens)->next;
			free_token(tmp->prev, free_ptr);
		}
		else
			tmp = tmp->next;
	}
	return ;
}

char	*var_joiner(t_token **token)
{
	t_token	*tp;
	char	*result;

	tp = *token;
	result = ft_strdup(tp->str);
	while (tp->type == VAR && tp->next->type == VAR && tp->next->join == true)
	{
		result = ft_strjoin(result, tp->next->str);
		tp = tp->next;
	}
	*token = tp;
	return (result);
}

char	**add_args_echo_tab(int len, char **tab, t_cmd *cmd, t_token *tmp)
{
	int	i;

	i = -1;
	while (++i < len)
		tab[i] = cmd->args[i];
	while (tmp->type == WORD || tmp->type == VAR)
	{
		if (tmp->join == true)
			tab[i] = var_joiner(&tmp);
		else
			tab[i] = ft_strdup(tmp->str);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (SUCCESS);
}
