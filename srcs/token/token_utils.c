/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: nigateau <nigateau@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/01/20 20:16:24 by nigateau          #+#    #+#             */
/*   Updated: 2025/01/20 20:16:24 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static t_bool	find_first_token(t_token *token, int i, int original_pos)
{
	while (i >= 0 && !is_pipe(token[i]))
		i--;
	if (i == -1 || is_pipe(token[i]))
		i++;
	if (token[i].type == CMD || token[i].type == BUILTIN)
		return (TRUE);
	if (token[i].type == OPERATOR)
	{
		i = original_pos;
		while (i >= 0 && token[i].type != OPERATOR)
		{
			i--;
			if ((token[i].type == CMD || token[i].type == BUILTIN) && token[i
					- 1].type != OPERATOR && token[i - 1].value[0] != '|')
				return (TRUE);
		}
		if (token[i].type == OPERATOR && token[i].value[0] != '|')
		{
			i = original_pos;
			if (token[i - 1].type == OPERATOR && token[i - 1].value[0] != '|')
				return (TRUE);
		}
	}
	return (FALSE);
}

static t_bool	check_operator(t_token *token, int i, int tlen)
{
	if (token[i].type == OPERATOR)
	{
		if ((i == 0 && is_pipe(token[i])) || (i == tlen - 1
				&& token[i].type == OPERATOR) || (token[i].value[0] == '|'
				&& token[i - 1].type == OPERATOR)
			|| (token[i].type == OPERATOR && token[i].value[0] != '|'
				&& token[i - 1].type == OPERATOR && token[i - 1].value[0]
				!= '|'))
			return (fprintf(stderr,
					"bash: syntax error near unexpected token `%s'\n",
					token[i].value), FALSE);
	}
	return (TRUE);
}

t_bool	second_pass(t_mini *shell)
{
	int	i;

	i = -1;
	while (++i < shell->tlen)
	{
		if (shell->token[i].type == OPERATOR)
			if (!check_operator(shell->token, i, shell->tlen))
				return (FALSE);
		if (shell->token[i].type == UNKNOWN)
		{
			if (find_first_token(shell->token, i, i) == TRUE)
				shell->token[i].type = STRING;
		}
	}
	return (TRUE);
}
