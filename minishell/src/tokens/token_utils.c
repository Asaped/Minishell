/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:58:58 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:04:33 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*create_token(char *str, char *str_copy, int type, int status)
{
	t_token	*result;

	result = malloc(sizeof(t_token));
	if (!result)
		return (NULL);
	result->str = str;
	result->str_copy = str_copy;
	result->exists = false;
	result->type = type;
	result->status = status;
	result->join = false;
	result->next = NULL;
	result->prev = NULL;
	return (result);
}

void	add_token(t_token **tokens, t_token *new)
{
	t_token	*start;

	start = *tokens;
	if (!start)
	{
		*tokens = new;
		return ;
	}
	if (tokens && *tokens && new)
	{
		while (start->next)
			start = start->next;
		start->next = new;
		new->prev = start;
		return ;
	}
}

void	free_token(t_token *token, void (*del)(void *))
{
	if (del && token && token->str)
	{
		(*del)(token->str);
		token->str = NULL;
	}
	if (del && token && token->str_copy)
	{
		(*del)(token->str_copy);
		token->str_copy = NULL;
	}
	if (token->prev)
		token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	(*del)(token);
}

void	free_tokenlst(t_token **tokens, void (*del)(void *))
{
	t_token	*tmp;

	tmp = NULL;
	while (*tokens)
	{
		tmp = (*tokens)->next;
		free_token(*tokens, del);
		*tokens = tmp;
	}
}
