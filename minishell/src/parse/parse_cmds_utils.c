/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:56:54 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:39:37 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Initialise les champs d'une structure de commande
static void	initialize_cmd(t_cmd **cmd)
{
	(*cmd)->command = NULL;
	(*cmd)->path = NULL;
	(*cmd)->args = NULL;
	(*cmd)->pipe_output = false;
	(*cmd)->pipe_fd = 0;
	(*cmd)->prev = NULL;
	(*cmd)->next = NULL;
}

// Crée une nouvelle structure de commande
// Définit `pipe_output` en fonction de la valeur passée
t_cmd	*cmd_creator(bool value)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!(new_node))
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_cmd));
	new_node->pipe_output = value;
	initialize_cmd(&new_node);
	return (new_node);
}

// Ajoute un nouvel élément à la fin de la liste de commandes
// Si la liste est vide, le nouvel élément devient le premier
void	cmd_adder(t_cmd **alst, t_cmd *new_node)
{
	t_cmd	*start;

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

// Renvoie le dernier élément de la liste de commandes
t_cmd	*last_cmd(t_cmd *cmd)
{
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}
