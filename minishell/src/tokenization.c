/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 12:08:38 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/15 17:31:11 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Identifier et parametrer tout les types de tokens correctement
// Ajout de l'ensemble de la chaine de tokens dans la structure data
// --> permettra de traiter les tokens directement depuis data

static void	lstadd_token(t_token **tokens, char *start, int len)
{
	t_token	*new_token;
	t_token	*tmp;

	new_token = (t_token *)safe_malloc(sizeof(t_token));
	if ((start[0] == '\'' || start[0] == '\"') && start[len - 1] == start[0])
		new_token->value = ft_strndup(start + 1, len - 2);
	else
		new_token->value = ft_strndup(start, len);
	new_token->next = NULL;
	if (!*tokens)
		*tokens = new_token;
	else
	{
		tmp = *tokens;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}

static int	token_len(t_tools *tools)
{
	int	len;

	len = 0;
	while (tools->input[len])
	{
		if ((tools->input[len] == '\'' || tools->input[len] == '\"'))
		{
			if (tools->quote_char == '\0')
			{
				tools->in_quote = true;
				tools->quote_char = tools->input[len];
			}
			else if (tools->input[len] == tools->quote_char)
			{
				tools->in_quote = false;
				tools->quote_char = '\0';
			}
		}
		else if (tools->input[len] == ' ' && !tools->in_quote)
			break ;
		len++;
	}
	return (len);
}

static int	init_tools_and_check_quote(t_data *data, t_tools *tools)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	tools->input = data->input;
	tools->in_quote = false;
	tools->quote_char = '\0';
	tools->len = 0;
	while (tools->input[++i])
	{
		if (tools->input[i] == '\'' || tools->input[i] == '\"')
			count++;
	}
	if ((count % 2) != 0)
		return (0);
	return (1);
}

int	init_tokens(t_data *data)
{
	t_tools	tools;
	t_token	*tokens;

	tokens = NULL;
	if (!init_tools_and_check_quote(data, &tools))
		return (0);
	if (!normalize_quotes(data))
		return (0);
	while (*tools.input)
	{
		tools.len = token_len(&tools);
		if (tools.len > 0)
		{
			lstadd_token(&tokens, tools.input, tools.len);
			tools.input += tools.len;
		}
		else
			tools.input++;
	}
	data->tokens = tokens;
	return (1);
}
