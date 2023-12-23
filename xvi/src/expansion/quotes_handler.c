/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:08:00 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:06:51 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	len_count(char *str, int count, int i)
{
	int	status;

	status = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && status == DEF)
		{
			if (str[i] == '\"')
				status = DQ;
			if (str[i] == '\'')
				status = SQ;
			i++;
			continue ;
		}
		else if ((str[i] == '\"' && status == DQ)
			|| (str[i] == '\'' && status == SQ))
		{
			status = DEF;
			i++;
			continue ;
		}
		count++;
		i++;
	}
	return (++count);
}

bool	str_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\"' || str[i] == '\'')
			return (true);
	return (false);
}

int	quote_handler(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if (str_quotes(tmp->str) == true
			&& (!tmp->prev || (tmp->prev && tmp->prev->type != HEREDOC)))
			quote_remover(&tmp);
		tmp = tmp->next;
	}
	return (0);
}
