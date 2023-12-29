/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_hdc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:59:57 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:44:35 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Convertit un tableau de chaînes en une seule chaîne séparée par des espaces
static char	*tab_to_str(char **tab)
{
	char	*str;
	char	*tmp;
	int		i;

	i = -1;
	while (tab[++i])
	{
		tmp = str;
		if (i == 0)
			str = ft_strdup(tab[0]);
		else
		{
			str = ft_strjoin(tmp, tab[i]);
			free_ptr(tmp);
		}
		if (tab[i + 1])
		{
			tmp = str;
			str = ft_strjoin(tmp, " ");
			free_ptr(tmp);
		}
	}
	free_tab(tab);
	return (str);
}

// Étend les variables dans une ligne de heredoc
// Divise la ligne en mots et étend les variables dans chaque mot
// Reconstruit et etourne la nouvelle ligne avec les variables étendues
static char	*get_expanded_var_line(t_data *data, char *line)
{
	char	**words;
	int		i;

	words = ft_split(line, ' ');
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		if (ft_strchr(words[i], '$'))
		{
			words[i] = var_expand_hdc(data, words[i]);
			if (!words[i])
				return (NULL);
		}
		i++;
	}
	return (tab_to_str(words));
}

// Vérifie une ligne de here-document pour l'expansion et la fin de delimiter
// Si la ligne correspond au délimiteur, termine le here-document
// Si des variables sont présentes et non entre quotes : expand
static bool	check_hdc_line(t_data *data, char **line, t_io_fds *io, bool *res)
{
	if (*line == NULL)
	{
		errmsg_cmd("warning", "here-document delimited by end-of-file: wanted",
			io->hdc_delimiter, true);
		*res = true;
		return (false);
	}
	if (ft_strcmp(*line, io->hdc_delimiter) == SUCCESS)
	{
		*res = true;
		return (false);
	}
	if (io->hdc_quotes == false && ft_strchr(*line, '$'))
	{
		*line = get_expanded_var_line(data, *line);
		if (!(*line))
		{
			free_ptr(*line);
			*res = false;
			return (false);
		}
	}
	return (true);
}

// Remplit le contenu d'un here-document dans un fichier temporaire
// Étend les variables dans les lignes si nécessaire
// Écrit chaque ligne dans un fichier temporaire
bool	fill_heredoc(t_data *data, t_io_fds *io, int fd)
{
	char	*line;
	bool	ret;

	ret = false;
	line = NULL;
	while (1)
	{
		signals_on();
		line = readline(">");
		signals_off();
		if (!check_hdc_line(data, &line, io, &ret))
			break ;
		ft_putendl_fd(line, fd);
		free_ptr(line);
	}
	free_ptr(line);
	return (ret);
}
