/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_extractor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:25:11 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/16 19:24:39 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	extract_in_quotes(char **input, char limit, t_token **tok)
{
	char	*str_token;
	int		i;
	t_token	*new_token;

	new_token = safe_malloc(sizeof(t_token));
	i = 0;
	(*input)++;
	str_token = safe_malloc(ft_strlen(*input) + 1);
	while (**input && **input != limit)
	{
		str_token[i++] = **input;
		(*input)++;
	}
	str_token[i] = '\0';
	if (**input == limit)
		(*input)++;
	new_token->value = str_token;
	new_token->len = ft_strlen(str_token);
	new_token->type = WORD;
	return (add_token(tok, new_token));
}

void	extract_d_redir(char **input, char redir, t_token **tok)
{
	char	*str_token;
	t_token	*new_token;

	new_token = safe_malloc(sizeof(t_token));
	str_token = safe_malloc(sizeof(char) * 3);
	str_token[0] = redir;
	str_token[1] = redir;
	str_token[2] = '\0';
	(*input) += 2;
	(void)input;
	new_token->len = 2;
	new_token->value = str_token;
	if (str_token[0] == '>')
		new_token->type = REDIR_APD;
	else
		new_token->type = REDIR_HDC;
	return (add_token(tok, new_token));
}

void	extract_s_redir(char **input, char redir, t_token **tok)
{
	char	*str_token;
	t_token	*new_token;

	new_token = safe_malloc(sizeof(t_token));
	str_token = safe_malloc(sizeof(char) * 2);
	str_token[0] = redir;
	str_token[1] = '\0';
	(*input)++;
	(void)input;
	new_token->len = 1;
	new_token->value = str_token;
	if (str_token[0] == '<')
		new_token->type = REDIR_IN;
	else
		new_token->type = REDIR_OUT;
	return (add_token(tok, new_token));
}

void	extract_operator(char **input, char oper, t_token **tok)
{
	char	*str_token;
	t_token	*new_token;

	new_token = safe_malloc(sizeof(t_token));
	str_token = safe_malloc(sizeof(char) * 2);
	str_token[0] = oper;
	str_token[1] = '\0';
	(*input)++;
	(void)input;
	new_token->len = 1;
	new_token->value = str_token;
	if (oper == '|')
		new_token->type = PIPE;
	if (oper == '=')
		new_token->type = ASSIGN;
	if (oper == ' ')
		new_token->type = SPACE;
	return (add_token(tok, new_token));
}

void	extract_words(char **input, t_token **tok)
{
	t_token	*new_token;
	char	*tok_str;
	int		i;

	i = 0;
	new_token = safe_malloc(sizeof(t_token));
	tok_str = safe_malloc(ft_strlen(*input) + 1);
	while (**input && is_valid_word(**input))
	{
		tok_str[i++] = **input;
		(*input)++;
	}
	tok_str[i] = '\0';
	if (**input)
		(*input)++;
	new_token->value = tok_str;
	new_token->len = ft_strlen(tok_str);
	new_token->type = WORD;
	return (add_token(tok, new_token));
}
