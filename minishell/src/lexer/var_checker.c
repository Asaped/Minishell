/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:43:57 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:24:17 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Vérifie si le token actuel contient une variable
// Si '$' est trouvé et que le token n'est pas dans un heredoc: token = VAR
static void	variable_check(t_token **token_node)
{
	int	i;

	i = 0;
	while ((*token_node)->str[i])
	{
		if ((*token_node)->str[i] == '$')
		{
			if ((*token_node)->prev && (*token_node)->prev->type == HEREDOC)
				break ;
			(*token_node)->type = VAR;
			return ;
		}
		i++;
	}
}

// Vérifie si un token est une variable
// Vérifie les erreurs de syntaxe
int	check_if_var(t_token **token_lst)
{
	t_token	*temp;

	temp = *token_lst;
	if (temp->type == PIPE)
	{
		errmsg("syntax error near unexpected token", temp->str, true);
		return (FAILURE);
	}
	while (temp)
	{
		variable_check(&temp);
		if (check_consecutives(&temp) == FAILURE)
			return (FAILURE);
		temp = temp->next;
	}
	return (SUCCESS);
}
