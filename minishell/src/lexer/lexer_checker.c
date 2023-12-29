/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:44:30 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:13:35 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Vérifie si deux opérateurs consécutifs sont présents dans les tokens
// Incluent les opérateurs de pipe consécutifs et les opérateurs à la fin
static bool	consecutive_ops(t_token *token_node)
{
	if (token_node->prev)
	{
		if (token_node->type == PIPE && token_node->prev->type == PIPE)
			return (true);
		if (token_node->type > PIPE && token_node->prev->type > PIPE)
			return (true);
		if (token_node->type == END && token_node->prev->type >= PIPE)
			return (true);
	}
	return (false);
}

// Utilise `consecutive_ops` pour chaque token.
// En cas d'opérateurs consécutifs, affiche un message d'erreur syntaxe
int	check_consecutives(t_token **token_lst)
{
	t_token	*temp;

	temp = *token_lst;
	while (temp)
	{
		if (consecutive_ops(temp) == true)
		{
			if (temp->type == END && temp->prev && temp->prev->type > PIPE)
				errmsg("syntax error unexpected token", "newline", 1);
			else if (temp->type == END && temp->prev)
				errmsg("syntax error unexpected token", temp->prev->str, 1);
			else
				errmsg("syntax error unexpected token", temp->str, 1);
			return (FAILURE);
		}
		temp = temp->next;
	}
	return (SUCCESS);
}
