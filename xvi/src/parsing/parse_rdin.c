/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:21:59 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 20:02:42 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	open_outfile(t_io_fds *io, char *file, char *origin)
{
	if (!del_prev_file(io, false))
		return ;
	io->outfile = ft_strdup(file);
	if (io->outfile && io->outfile[0] == '\0')
	{
		errmsg_cmd(origin, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (io->fd_out == -1)
		errmsg_cmd(io->outfile, NULL, strerror(errno), false);
}

void	parse_redirin(t_cmd **cmds, t_token **tokens)
{
	t_token	*tmp;
	t_cmd	*cmd;

	tmp = *tokens;
	cmd = last_cmd(*cmds);
	init_io(cmd);
	open_outfile(cmd->io_fds, tmp->next->str, tmp->next->str_copy);
	if (tmp->next->next)
		tmp = tmp->next->next;
	else
		tmp = tmp->next;
	*tokens = tmp;
}
