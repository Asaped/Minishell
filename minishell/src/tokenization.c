/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 12:08:38 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/16 19:20:21 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	parse_input(t_data *data)
{
	t_token	*tok;
	t_tools	tools;

	init_token_tools(&tools, data);
	tok = safe_malloc(sizeof(t_token));
	printf("input parse 1: - %s -\n", tools.input);
	while (*tools.input)
	{
		if (ft_isquote(*tools.input))
			extract_in_quotes(&(tools.input), *tools.input, &tok);
		else if (*tools.input == '>' || *tools.input == '<')
		{
			if (*tools.input == *(tools.input + 1))
				extract_d_redir(&(tools.input), *tools.input, &tok);
			else
				extract_s_redir(&(tools.input), *tools.input, &tok);
		}
		else if (ft_isoperator(*tools.input))
			extract_operator(&(tools.input), *tools.input, &tok);
		else if (is_valid_word(*tools.input))
			extract_words(&(tools.input), &tok);
		else
			tools.input++;
	}
	data->tokens = tok;
}

void	print_tok(t_token *tokens_lst)
{
	t_token	*tmp;

	tmp = tokens_lst;
	while (tmp != NULL)
	{
		printf("token: %s - type: %d - len: %d\n", tmp->value, tmp->type, tmp->len);
		tmp = tmp->next;
	}
}

int	init_tokens(t_data *data)
{
	if (!formats_and_checks(data))
		return (0);
	parse_input(data);
	print_tok(data->tokens);
	return (1);
}
