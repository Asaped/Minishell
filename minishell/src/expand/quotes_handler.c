/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 15:10:32 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 12:47:00 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Compte la longueur d'une chaîne en tenant compte des quotes
// Ignore les caractères à l'intérieur des quotes simples ou doubles
// Utilisé pour trouver la taille nécessaire pour stocker str sans les quotes
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

// Vérifie si une chaîne contient des quotes simples ou doubles
bool	has_quote(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
	}
	return (false);
}

// Parcourt tous les tokens et supprime les quotes si nécessaire
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
