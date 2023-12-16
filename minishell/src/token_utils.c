/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:21:15 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/16 19:14:48 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_token_tools(t_tools *tools, t_data *data)
{
	tools->in_quote = false;
	tools->input = data->input;
	tools->len = 0;
}

t_token	*create_token(t_type_token type, char *value, int len)
{
	t_token	*token;

	token = safe_malloc(sizeof(t_token));
	token->type = type;
	token->value = value;
	token->len = len;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*last_token;

	if (*tokens == NULL)
	{
		*tokens = new_token;
		return ;
	}
	last_token = *tokens;
	while (last_token->next)
		last_token = last_token->next;
	last_token->next = new_token;
	new_token->prev = last_token;
}
