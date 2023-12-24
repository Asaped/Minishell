/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 15:10:32 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/24 15:10:42 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_len(char *str, int count, int i)
{
	int	status;

	status = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && status == DEFAULT)
		{
			if (str[i] == '\'')
				status = SQ;
			if (str[i] == '\"')
				status = DQ;
			i++;
			continue ;
		}
		else if ((str[i] == '\'' && status == SQ)
			|| (str[i] == '\"' && status == DQ))
		{
			status = DEFAULT;
			i++;
			continue ;
		}
		count++;
		i++;
	}
	return (count + 1);
}

bool	has_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

int	quotes_handler(t_data *data)
{
	t_token	*temp;

	temp = data->token;
	while (temp)
	{
		if (has_quote(temp->str) == true
			&& (!temp->prev || (temp->prev && temp->prev->type != HEREDOC)))
			quotes_remover(&temp);
		temp = temp->next;
	}
	return (0);
}
