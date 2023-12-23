/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:44:32 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:04:57 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	io_restore(t_io_fds *io)
{
	bool	result;

	result = true;
	if (!io)
		return (true);
	if (io->stdin_copy != -1)
	{
		if (dup2(io->stdin_copy, STDIN_FILENO) == -1)
			result = false;
		close(io->stdin_copy);
		io->stdin_copy = -1;
	}
	if (io->stdout_copy != -1)
	{
		if (dup2(io->stdout_copy, STDOUT_FILENO) == -1)
			result = false;
		close(io->stdout_copy);
		io->stdout_copy = -1;
	}
	return (result);
}

bool	io_redir(t_io_fds *io)
{
	int	res;

	res = true;
	if (!io)
		return (res);
	io->stdin_copy = dup(STDIN_FILENO);
	if (io->stdin_copy == -1)
		res = errmsg_cmd("dup", "stdin_copy", strerror(errno), false);
	io->stdout_copy = dup(STDOUT_FILENO);
	if (io->stdout_copy == -1)
		res = errmsg_cmd("dup", "stdout_copy", strerror(errno), false);
	if (io->fd_in == -1)
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			res = errmsg_cmd("dup2", io->infile, strerror(errno), false);
	if (io->fd_out == -1)
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			res = errmsg_cmd("dup2", io->outfile, strerror(errno), false);
	return (res);
}

bool	if_of_checker(t_io_fds *io)
{
	if (!io || (!io->infile && !io->outfile))
		return (true);
	if ((io->infile && io->fd_in == -1) || (io->outfile && io->fd_out == -1))
		return (false);
	return (true);
}
