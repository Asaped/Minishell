/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:59:34 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:36:21 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Ouvre ou crée un fichier pour la redir de type "append" (>>)
// Vérifie d'abord si une précédente réf de fichier est à supprimer
// Duplique le nom du fichier et ouvre ou crée le fichier avec les bons droits
static void	open_of_append(t_io_fds *io, char *file, char *var_filename)
{
	if (!remove_old_file_ref(io, false))
		return ;
	io->outfile = ft_strdup(file);
	if (io->outfile && io->outfile[0] == '\0' && var_filename)
	{
		errmsg_cmd(var_filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (io->fd_out == -1)
		errmsg_cmd(io->outfile, NULL, strerror(errno), false);
}

// Analyse et traite un opérateur d'append (>>) dans la commande
// Récupère le nom du fichier suivant l'opérateur '>>' pour la redirection
// Initialise les I/O de la commande et gère l'ouverture du fichier
// Avance le pointeur de token pour traiter la suite de la commande
void	parse_append(t_cmd **last, t_token **token_lst)
{
	t_token	*temp;
	t_cmd	*cmd;

	temp = *token_lst;
	cmd = last_cmd(*last);
	init_io(cmd);
	open_of_append(cmd->io_fds, temp->next->str, temp->next->str_copy);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
