/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:46:35 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:17:27 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Crée un nouveau token avec les valeurs fournies.
// Initialise les pointeurs 'prev' et 'next' à NULL.
// Utilisé pour générer des tokens lors du lexing.
t_token	*create_token(char *str, char *str_copy, int type, int status)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token) * 1);
	if (!(new_node))
		return (NULL);
	new_node->str = str;
	new_node->str_copy = str_copy;
	new_node->var_exists = false;
	new_node->type = type;
	new_node->status = status;
	new_node->join = false;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

// Ajoute un token à la fin de la liste de tokens
// Si la liste est vide, le nouveau token devient la tête de la liste
// Assure que les pointeurs 'prev' et 'next' sont bien configurés
void	add_token(t_token **alst, t_token *new_node)
{
	t_token	*start;

	start = *alst;
	if (start == NULL)
	{
		*alst = new_node;
		return ;
	}
	if (alst && *alst && new_node)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = new_node;
		new_node->prev = start;
	}
}

// Supprime un SEUL token de la liste et libère sa mémoire.
// Met à jour les pointeurs 'prev' et 'next' des tokens adjacents
void	delete_token(t_token *lst, void (*del)(void *))
{
	if (del && lst && lst->str)
	{
		(*del)(lst->str);
		lst->str = NULL;
	}
	if (del && lst && lst->str_copy)
	{
		(*del)(lst->str_copy);
		lst->str_copy = NULL;
	}
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
	free_ptr(lst);
}

// Supprime et libère la mémoire de tous les tokens d'une liste
void	clear_tokens(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	tmp = NULL;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		delete_token(*lst, del);
		*lst = tmp;
	}
}
