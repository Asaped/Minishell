/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_cleaner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:12:15 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:49:27 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	set_quotes(t_token **token, int *i)
{
	if ((*token)->str[*i] == '\'')
		(*token)->status = SQ;
	if ((*token)->str[*i] == '\"')
		(*token)->status = DQ;
	(*i)++;
}

static bool	set_default(t_token **token, int *i)
{
	if (((*token)->str[*i] == '\'' && (*token)->status == SQ)
		|| ((*token)->str[*i] == '\"' && (*token)->status == DQ))
	{
		(*token)->status = DEF;
		(*i)++;
		return (true);
	}
	else
		return (false);
}

static bool	status_and_quotes(t_token **token, int *i)
{
	if ((*token)->status == DEF
		&& ((*token)->str[*i] == '\'' || (*token)->str[*i] == '\"'))
		return (true);
	return (false);
}

int	quote_remover(t_token **tokens)
{
	char	*result;
	int		i;
	int		k;

	i = 0;
	k = 0;
	result = malloc(sizeof(char) * len_count((*tokens)->str, i, i));
	if (!result)
		return (1);
	while ((*tokens)->str[i])
	{
		if (status_and_quotes(tokens, &i) == true)
		{
			set_quotes(tokens, &i);
			continue ;
		}
		else if (set_default(tokens, &i) == true)
			continue ;
		result[k++] = (*tokens)->str[i++];
	}
	result[k] = '\0';
	free_ptr((*tokens)->str);
	(*tokens)->str = result;
	(*tokens)->join = true;
	return (0);
}
