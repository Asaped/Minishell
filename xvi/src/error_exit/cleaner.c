/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:32:20 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:44:14 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_data(t_data *data, bool history)
{
	if (data && data->user_input)
	{
		free_ptr(data->user_input);
		data->user_input = NULL;
	}
	if (data && data->token)
		free_tokenlst(&data->token, &free_ptr);
	if (data && data->cmd)
		free_cmdlst(&data->cmd, &free_ptr);
	if (history == true)
	{
		if (data && data->wdir)
			free_ptr(data->wdir);
		if (data && data->old_wdir)
			free_ptr(data->old_wdir);
		if (data && data->env)
			free_tab(data->env);
		clear_history();
	}
}

void	close_fds(t_cmd *cmds, bool cl_backup)
{
	if (cmds->io_fds)
	{
		if (cmds->io_fds->fd_in != -1)
			close(cmds->io_fds->fd_in);
		if (cmds->io_fds->fd_out != -1)
			close(cmds->io_fds->fd_out);
		if (cl_backup)
			io_restore(cmds->io_fds);
	}
	close_pipe_fds(cmds, NULL);
}

void	free_io(t_io_fds *io)
{
	if (!io)
		return ;
	io_restore(io);
	if (io->hdc_delimiter)
	{
		unlink(io->infile);
		free_ptr(io->hdc_delimiter);
	}
	if (io->infile)
		free_ptr(io->infile);
	if (io->outfile)
		free_ptr(io->outfile);
	if (io)
		free_ptr(io);
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i])
	{
		if (tab[i])
		{
			free_ptr(tab[i]);
			tab[i] = NULL;
		}
	}
	free(tab);
	tab = NULL;
}

void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}
