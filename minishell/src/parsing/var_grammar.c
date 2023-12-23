/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_grammar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:41:17 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 20:10:04 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	consecutive(t_token *token)
{
	if (token->prev)
	{
		if (token->type == PIPE && token->prev->type == PIPE)
			return (true);
		if (token->type > PIPE && token->prev->type > PIPE)
			return (true);
		if (token->type == END && token->prev->type >= PIPE)
			return (true);
	}
	return (false);
}

int	check_consecutives(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if (consecutive(tmp) == true)
		{
			if (tmp->type == END && tmp->prev && tmp->prev->type == PIPE)
				errmsg("error syntax near token", "newline", true);
			else if (tmp->type == END && tmp->prev)
				errmsg("error syntax near token", tmp->prev->str, true);
			else
				errmsg("error syntax near token", tmp->str, true);
			return (FAILURE);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
