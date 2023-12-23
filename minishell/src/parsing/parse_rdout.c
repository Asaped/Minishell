/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rdout.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:58:54 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:05:47 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	del_prev_file(t_io_fds *io, bool infile)
{
	if (infile == true && io->infile)
	{
		if (io->fd_in == -1 || (io->outfile && io->fd_out == -1))
			return (false);
		if (io->hdc_delimiter)
		{
			free_ptr(io->hdc_delimiter);
			io->hdc_delimiter = NULL;
			unlink(io->infile);
		}
		free_ptr(io->infile);
		close(io->fd_in);
	}
	else if (infile == false && io->infile)
	{
		if (io->fd_out == -1 || (io->infile && io->fd_in == -1))
			return (false);
		free_ptr(io->outfile);
		close(io->fd_out);
	}
	return (true);
}

static void	open_infile(t_io_fds *io, char *file, char *origin)
{
	if (!del_prev_file(io, true))
		return ;
	io->infile = ft_strdup(file);
	if (io->infile && io->infile[0] == '\0')
	{
		errmsg_cmd(origin, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_in = open(io->infile, O_RDONLY);
	if (io->fd_in == -1)
		errmsg_cmd(io->infile, NULL, strerror(errno), false);
}

void	parse_redirout(t_cmd **cmds, t_token **tokens)
{
	t_token	*tmp;
	t_cmd	*cmd;

	tmp = *tokens;
	cmd = last_cmd(*cmds);
	init_io(cmd);
	open_infile(cmd->io_fds, tmp->next->str, tmp->next->str_copy);
	if (tmp->next->next)
		tmp = tmp->next->next;
	else
		tmp = tmp->next;
	*tokens = tmp;
}
