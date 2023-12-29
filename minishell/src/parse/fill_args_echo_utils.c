/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args_echo_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:58:33 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:32:48 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Rejoint plusieurs tokens de type VAR en une seul string
// Utilisé pour gérer les cas où plusieurs venv sont concaténées
char	*venv_joiner(t_token **token_node)
{
	t_token	*temp;
	char	*str;

	temp = *token_node;
	str = ft_strdup(temp->str);
	while (temp->type == VAR && temp->next->type == VAR
		&& temp->next->join == true)
	{
		str = ft_strjoin(str, temp->next->str);
		temp = temp->next;
	}
	*token_node = temp;
	return (str);
}

// Compte le nombre d'arguments en tenant compte des variables et mots
// Traite les cas où plusieurs variables sont jointes en une seule
int	args_counter(t_token *temp)
{
	int	i;

	i = 0;
	while (temp && (temp->type == WORD || temp->type == VAR))
	{
		if (temp->type == VAR && temp->join == true)
		{
			while (temp->type == VAR && temp->join == true)
				temp = temp->next;
			i++;
		}
		else
		{
			i++;
			temp = temp->next;
		}
	}
	return (i);
}

// Duplique un tableau d'arguments et ajoute de nouveaux arguments
// Utilisé pour ajouter des arguments supplémentaires à une commande existante
char	**tab_duplicate(int len, char **tab, t_cmd *last, t_token *tmp)
{
	int	i;

	i = -1;
	while (++i < len)
		tab[i] = last->args[i];
	while (tmp->type == WORD || tmp->type == VAR)
	{
		if (tmp->join == true)
			tab[i] = venv_joiner(&tmp);
		else
			tab[i] = ft_strdup(tmp->str);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

// Supprime les tokens vides de la liste
// Ces tokens vides peuvent se produire lors de l'expansion des venv
void	venv_remove_empty(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	while (temp->type == WORD || temp->type == VAR)
	{
		if (temp->type == VAR && temp->str[0] == '\0'
			&& temp->var_exists == false)
		{
			temp = temp->next;
			if (temp == (*tokens)->next)
				(*tokens) = (*tokens)->next;
			delete_token(temp->prev, free_ptr);
		}
		else
			temp = temp->next;
	}
}
