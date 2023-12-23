/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:50:04 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 20:33:25 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	set_type(int status, char *str, int i)
{
	if (str[i] == '\'' && status == DEF)
		status = SQ;
	else if (str[i] == '\"' && status == DEF)
		status = DQ;
	else if (str[i] == '\'' && status == SQ)
		status = DEF;
	else if (str[i] == '\"' && status == DQ)
		status = DEF;
	return (status);
}

int	is_sep(char *str, int i)
{
	if ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		return (SPACES);
	else if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	else if (str[i] == '>')
		return (REDIR_OUT);
	else if (str[i] == '<')
		return (REDIR_IN);
	else if (str[i] == '\0')
		return (END);
	else
		return (0);
}

int	set_word(t_token **token, char *str, int i, int start)
{
	char	*result;
	int		k;

	k = 0;
	result = malloc(sizeof(char) * (i - start) + 1);
	if (!result)
		return (1);
	while (start < i)
		result[k++] = str[start++];
	result[k] = '\0';
	add_token(token, create_token(result, ft_strdup(result), WORD, DEF));
	return (0);
}

int	set_sep(t_token **tokens, char *str, int i, int type)
{
	char	*sep;

	if (type == APPEND || type == HEREDOC)
	{
		sep = malloc(sizeof(char) * 3);
		if (!sep)
			return (1);
		sep[0] = str[i++];
		sep[1] = str[i++];
		sep[2] = '\0';
	}
	else
	{
		sep = malloc(sizeof(char) * 2);
		if (!sep)
			return (1);
		sep[0] = str[i++];
		sep[1] = '\0';
	}
	add_token(tokens, create_token(sep, NULL, type, DEF));
	return (0);
}

int	set_word_sep(int *i, char *str, int start, t_data *data)
{
	int	type;

	type = is_sep(str, *i);
	if (type)
	{
		if (*i && !is_sep(str, (*i) - 1))
			set_word(&data->token, str, *i, start);
		if (type == APPEND || type == HEREDOC || type == PIPE
			|| type == REDIR_IN || type == REDIR_OUT || type == END)
		{
			set_sep(&data->token, str, *i, type);
			if (type == APPEND || type == HEREDOC)
				(*i)++;
		}
		start = (*i) + 1;
	}
	return (start);
}
