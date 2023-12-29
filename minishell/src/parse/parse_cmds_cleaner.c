/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds_cleaner.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:56:31 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:37:40 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Supprime une commande de la liste de commandes
// Libère la mémoire allouée pour la commande, ses arguments et les I/O
void	cmd_remover(t_cmd *lst, void (*del)(void *))
{
	if (lst->command)
		(*del)(lst->command);
	if (lst->args)
		free_tab(lst->args);
	if (lst->pipe_fd)
		(*del)(lst->pipe_fd);
	if (lst->io_fds)
		free_io(lst->io_fds);
	(*del)(lst);
}

// Parcourt et supprime toutes les commandes de la liste.
void	cmds_clear(t_cmd **lst, void (*del)(void *))
{
	t_cmd	*temp;

	temp = NULL;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		cmd_remover(*lst, del);
		*lst = temp;
	}
}
