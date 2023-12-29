/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_trunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 13:01:51 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 14:01:48 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Convertit chemin relatif en absolu si nécessaire
// Ajoute "./" pour chemin relatif
char	*get_rel_path(char *file_to_open)
{
	char	*path;
	char	*res;

	if (file_to_open[0] == '/')
		return (ft_strdup(file_to_open));
	path = ft_strdup("./");
	res = ft_strjoin(path, file_to_open);
	printf("PARSING - Get_rel_path function return : %s\n", res);
	return (res);
}

// Ouvre fichier pour redirection sortie avec troncature
// Gère suppression références précédentes
// Définit descripteur de fichier `fd_out` & gère erreurs d'ouverture.
static void	open_outfile_trunc(t_io_fds *io, char *file, char *var_filename)
{
	if (!remove_old_file_ref(io, false))
		return ;
	io->outfile = ft_strdup(file);
	if (io->outfile && io->outfile[0] == '\0')
	{
		errmsg_cmd(var_filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (io->fd_out == -1)
		errmsg_cmd(io->outfile, NULL, strerror(errno), false);
}

// Analyse redirection de sortie avec troncature (opérateur '>'). Init I/O
// Utilise `open_outfile_trunc` pour ouvrir fichier de sortie
void	parse_trunc(t_cmd **last, t_token **token_lst)
{
	t_token	*temp;
	t_cmd	*cmd;

	temp = *token_lst;
	cmd = last_cmd(*last);
	init_io(cmd);
	open_outfile_trunc(cmd->io_fds, temp->next->str, temp->next->str_copy);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
