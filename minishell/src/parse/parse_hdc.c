/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_hdc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 13:00:21 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:47:54 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Exécute et gère la création d'un heredoc
// Ouvre un fichier temporaire pour stocker le contenu
// Appelle 'fill_heredoc' pour remplir le fichier avec le contenu
// Ferme le fichier temp après l'achèvement
bool	get_heredoc(t_data *data, t_io_fds *io)
{
	int		tmp_fd;
	bool	res;

	res = true;
	tmp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	res = fill_heredoc(data, io, tmp_fd);
	close(tmp_fd);
	return (res);
}

// Génère un nom unique pour un fichier temporaire de heredoc
// Utilise un compteur statique pour assurer des noms uniques
// Concatène un préfixe prédéfini avec un numéro incrémenté
static char	*get_heredoc_name(void)
{
	static int	i;
	char		*name;
	char		*number;

	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(HEREDOC_NAME, number);
	free(number);
	i++;
	return (name);
}

// Extrait et nettoie le délimiteur d'un hererdoc
// Vérifie si le délimiteur est entre quotes simples ou doubles
// Enlève les guillemets du délimiteur si nécessaire
// Utilisé pour terminer la saisie du here-document
static char	*get_delim(char *delim, bool *quotes)
{
	int	len;

	len = ft_strlen(delim) - 1;
	if ((delim[0] == '\"' && delim[len] == '\"')
		|| (delim[0] == '\'' && delim[len] == '\''))
	{
		*quotes = true;
		return (ft_strtrim(delim, "\'\""));
	}
	return (ft_strdup(delim));
}

// Analyse et initialise un heredoc dans la commande
// Crée une structure pour gérer les entrées/sorties
// Génère un nom de fichier temporaire pour stocker le contenu
// Extrait le délimiteur et gère les guillemets
// Lit et stocke le contenu si le délimiteur est atteint
// Joint le fichier temporaire à l'entrée standard de la commande
void	parse_heredoc(t_data *data, t_cmd **last, t_token **token_lst)
{
	t_token		*temp;
	t_cmd		*cmd;
	t_io_fds	*io;

	temp = *token_lst;
	cmd = last_cmd(*last);
	init_io(cmd);
	io = cmd->io_fds;
	if (!remove_old_file_ref(io, true))
		return ;
	io->infile = get_heredoc_name();
	io->hdc_delimiter = get_delim(temp->next->str, &(io->hdc_quotes));
	if (get_heredoc(data, io))
		io->fd_in = open(io->infile, O_RDONLY);
	else
		io->fd_in = -1;
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
