/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remover.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:40:43 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 12:49:15 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Change le statut du token en fonction du type de quote rencontré
// S'utilise pour gérer correctement les quotes dans les tokens
static void	change_status_to_quote(t_token **token_node, int *i)
{
	if ((*token_node)->str[*i] == '\'')
		(*token_node)->status = SQ;
	if ((*token_node)->str[*i] == '\"')
		(*token_node)->status = DQ;
	(*i)++;
}

// Vérifie si le char actuel est une quote et si le token est en mode défaut
// Utilisé pour détecter le début ou la fin des quotes dans un token
static bool	if_quotes_and_default(t_token **token_node, int i)
{
	if (((*token_node)->str[i] == '\'' || (*token_node)->str[i] == '\"')
		&& (*token_node)->status == DEFAULT)
		return (true);
	else
		return (false);
}

// Change le statut du token de quote à par défaut si nécessaire
// Utilisé pour marquer la fin d'une séquence de quotes dans un token
static bool	change_back_to_default(t_token **token_node, int *i)
{
	if (((*token_node)->str[*i] == '\'' && (*token_node)->status == SQ)
		|| ((*token_node)->str[*i] == '\"' && (*token_node)->status == DQ))
	{
		(*token_node)->status = DEFAULT;
		(*i)++;
		return (true);
	}
	else
		return (false);
}

// Supprime les quotes des tokens
// Utilisé pour normaliser les tokens avant l'exécution des commandes
int	quotes_remover(t_token **token_node)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * count_len((*token_node)->str, i, i));
	if (!new_line)
		return (1);
	while ((*token_node)->str[i])
	{
		if (if_quotes_and_default(token_node, i) == true)
		{
			change_status_to_quote(token_node, &i);
			continue ;
		}
		else if (change_back_to_default(token_node, &i) == true)
			continue ;
		new_line[j++] = (*token_node)->str[i++];
	}
	new_line[j] = '\0';
	free_ptr((*token_node)->str);
	(*token_node)->str = new_line;
	(*token_node)->join = true;
	return (0);
}
