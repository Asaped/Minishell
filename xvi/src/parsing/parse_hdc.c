/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_hdc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:39:07 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:58:40 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*generate_hdc_name(void)
{
	static int	i;
	char		*name;
	char		*nb;

	nb = ft_itoa(i++);
	if (!nb)
		return (NULL);
	name = ft_strjoin(HDC_NAME, nb);
	free(nb);
	return (name);
}

static char	*get_delim(char *str, bool *quotes)
{
	int	len;

	len = ft_strlen(str) - 1;
	if ((str[0] == '\"' && str[len] == '\"')
		|| (str[0] == '\'' && str[len] == '\''))
	{
		*quotes = true;
		return (ft_strtrim(str, "\'\""));
	}
	return (ft_strdup(str));
}

bool	get_hdc(t_data *data, t_io_fds *io)
{
	bool	result;
	int		tmp_fd;

	result = true;
	tmp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	result = fill_hdc(data, io, tmp_fd);
	close(tmp_fd);
	return (result);
}

void	parse_heredoc(t_data *data, t_cmd **cmds, t_token **tokens)
{
	t_token		*tmp;
	t_cmd		*cmd;
	t_io_fds	*io;

	tmp = *tokens;
	cmd = last_cmd(*cmds);
	init_io(cmd);
	io = cmd->io_fds;
	if (!del_prev_file(io, true))
		return ;
	io->infile = generate_hdc_name();
	io->hdc_delimiter = get_delim(tmp->next->str, &(io->hdc_quotes));
	if (get_hdc(data, io))
		io->fd_in = open(io->infile, O_RDONLY);
	else
		io->fd_in = -1;
	if (tmp->next->next)
		tmp = tmp->next->next;
	else
		tmp = tmp->next;
	*tokens = tmp;
}
