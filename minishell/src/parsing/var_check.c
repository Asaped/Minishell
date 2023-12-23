/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:28:25 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:05:18 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	check_var(t_token **tokens)
{
	int	i;

	i = -1;
	while ((*tokens)->str[++i])
	{
		if ((*tokens)->str[i] == '$')
		{
			if ((*tokens)->prev && (*tokens)->prev->type == HEREDOC)
				break ;
			(*tokens)->type = VAR;
			return ;
		}
	}
}

int	is_var(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	if (tmp->type == PIPE)
	{
		errmsg("syntax error, unexpected token", tmp->str, true);
		return (FAILURE);
	}
	while (tmp)
	{
		check_var(&tmp);
		if (check_consecutives(&tmp) == FAILURE)
			return (FAILURE);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
