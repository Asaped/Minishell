/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 13:02:53 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/26 09:32:21 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	io_restorer(t_io_fds *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	if (io->stdin_copy != -1)
	{
		if (dup2(io->stdin_copy, STDIN_FILENO) == -1)
			ret = false;
		close(io->stdin_copy);
		io->stdin_copy = -1;
	}
	if (io->stdout_copy != -1)
	{
		if (dup2(io->stdout_copy, STDOUT_FILENO) == -1)
			ret = false;
		close(io->stdout_copy);
		io->stdout_copy = -1;
	}
	return (ret);
}

bool	io_redirecter(t_io_fds *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	io->stdin_copy = dup(STDIN_FILENO);
	if (io->stdin_copy == -1)
		ret = errmsg_cmd("dup", "stdin backup", strerror(errno), false);
	io->stdout_copy = dup(STDOUT_FILENO);
	if (io->stdout_copy == -1)
		ret = errmsg_cmd("dup", "stdout backup", strerror(errno), false);
	if (io->fd_in != -1)
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			ret = errmsg_cmd("dup2", io->infile, strerror(errno), false);
	if (io->fd_out != -1)
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			ret = errmsg_cmd("dup2", io->outfile, strerror(errno), false);
	return (ret);
}

bool	check_if_of(t_io_fds *io)
{
	if (!io || (!io->infile && !io->outfile))
		return (true);
	if ((io->infile && io->fd_in == -1)
		|| (io->outfile && io->fd_out == -1))
		return (false);
	return (true);
}
