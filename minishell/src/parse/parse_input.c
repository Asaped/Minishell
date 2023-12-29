/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 13:00:53 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:50:57 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Gère la suppression de références aux fichiers IF/OF précédents
// Si 'infile' est 'true', il se concentre sur le infile, sinon sur le outfile
// Supprime le délimiteur et le fichier temporaire associé si nécessaire
bool	remove_old_file_ref(t_io_fds *io, bool infile)
{
	if (infile == true && io->infile)
	{
		if (io->fd_in == -1 || (io->outfile && io->fd_out == -1))
			return (false);
		if (io->hdc_delimiter != NULL)
		{
			free_ptr(io->hdc_delimiter);
			io->hdc_delimiter = NULL;
			unlink(io->infile);
		}
		free_ptr(io->infile);
		close(io->fd_in);
	}
	else if (infile == false && io->outfile)
	{
		if (io->fd_out == -1 || (io->infile && io->fd_in == -1))
			return (false);
		free_ptr(io->outfile);
		close(io->fd_out);
	}
	return (true);
}

// Ouvre un fichier pour la redirection d'input
// Supprime les anciennes références d'infile
// Duplique le chemin d'infile & vérifie les erreurs de redirection
// Ouvre le fichier d'entrée et met à jour le fd dans 'io_fds'
static void	open_infile(t_io_fds *io, char *file, char *original_filename)
{
	if (!remove_old_file_ref(io, true))
		return ;
	io->infile = ft_strdup(file);
	if (io->infile && io->infile[0] == '\0')
	{
		errmsg_cmd(original_filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_in = open(io->infile, O_RDONLY);
	if (io->fd_in == -1)
		errmsg_cmd(io->infile, NULL, strerror(errno), false);
}

// Analyse et traite la redirection d'entrée pour une commande
// Obtient la dernière commande ajoutée
// Initialise les structures de gestion des entrées/sorties
// Ouvre le fichier spécifié pour la redirection d'entrée
void	parse_input(t_cmd **last, t_token **token_lst)
{
	t_token	*temp;
	t_cmd	*cmd;

	temp = *token_lst;
	cmd = last_cmd(*last);
	init_io(cmd);
	open_infile(cmd->io_fds, temp->next->str, temp->next->str_copy);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
