/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:45:53 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:15:39 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Connecte un nouveau token dans la liste de tokens
// Assure que les pointeurs 'prev' et 'next' de tous les tokens sont à jour
// Utilisé lors de l'insertion d'un nouveau token dans la liste
static void	link_tokens(t_token *to_del, t_token *temp, t_token *insert)
{
	while (temp != to_del)
		temp = temp->next;
	insert->prev = temp->prev;
	temp->prev->next = insert;
	while (insert->next)
		insert = insert->next;
	temp->next->prev = insert;
	insert->next = temp->next;
}

// Insère un nouveau token dans la liste de tokens.
// Si le token à supprimer est la tête, le new token devient la nouvelle tête
// Sinon 'link_tokens' pour insérer le nouveau token à la place
// Renvoie le token nouvellement inséré.
t_token	*insert_token(t_token **head, t_token *to_del, t_token *insert)
{
	t_token	*temp;

	temp = *head;
	if (temp == NULL)
		*head = insert;
	else if (temp == to_del)
	{
		*head = insert;
		insert->next = temp->next;
		if (temp->next != NULL)
			temp->next->prev = insert;
	}
	else
		link_tokens(to_del, temp, insert);
	free_ptr(to_del->str);
	free_ptr(to_del);
	return (insert);
}
