/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_hdc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:53:32 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:57:39 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*tab_to_str(char **tab)
{
	char	*result;
	char	*tmp;
	int		i;

	i = -1;
	while (tab[++i])
	{
		tmp = result;
		if (i == 0)
			result = ft_strdup(tab[0]);
		else
		{
			result = ft_strjoin(tmp, tab[i]);
			free_ptr(tmp);
		}
		if (tab[i + 1])
		{
			tmp = result;
			result = ft_strjoin(tmp, " ");
			free_ptr(tmp);
		}
	}
	free_tab(tab);
	return (result);
}

static char	*get_expand_var(t_data *data, char *line)
{
	char	**tab;
	int		i;

	i = -1;
	tab = ft_split(line, ' ');
	if (!tab)
		return (NULL);
	while (tab[++i])
	{
		if (ft_strchr(tab[i], '$'))
		{
			tab[i] = var_expander_hdc(data, tab[i]);
			if (!tab[i])
				return (NULL);
		}
	}
	return (tab_to_str(tab));
}

static bool	check_hdc_line(t_data *data, char **line, t_io_fds *io, bool *res)
{
	if (!(*line))
	{
		errmsg_cmd("warning", "hdc delimited by EOF: wanted",
			io->hdc_delimiter, true);
		*res = true;
		return (false);
	}
	if (ft_strcmp(*line, io->hdc_delimiter) == 0)
	{
		*res = true;
		return (false);
	}
	if (io->hdc_quotes == false && ft_strchr(*line, '$'))
	{
		*line = get_expand_var(data, *line);
		if (!(*line))
		{
			free_ptr(*line);
			*res = false;
			return (false);
		}
	}
	return (true);
}

bool	fill_hdc(t_data *data, t_io_fds *io, int fd)
{
	char	*line;
	bool	result;

	line = NULL;
	result = false;
	while (1)
	{
		signals_on();
		line = readline("$> ");
		if (!check_hdc_line(data, &line, io, &result))
			break ;
		ft_putendl_fd(line, fd);
		free_ptr(line);
	}
	free_ptr(line);
	return (result);
}
