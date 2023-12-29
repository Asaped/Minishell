/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:33:10 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 12:08:20 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Libère les ressoruces de toute la structure, en supprimant ou non l'history
void	free_data(t_data *data, bool clear_history)
{
	if (data && data->user_input)
	{
		free_ptr(data->user_input);
		data->user_input = NULL;
	}
	if (data && data->token)
		clear_tokens(&data->token, &free_ptr);
	if (data && data->cmd)
		cmds_clear(&data->cmd, &free_ptr);
	if (clear_history == true)
	{
		if (data && data->wdir)
			free_ptr(data->wdir);
		if (data && data->old_wdir)
			free_ptr(data->old_wdir);
		if (data && data->env)
			free_tab(data->env);
		rl_clear_history();
	}
}

// Ferme les FD ouverts par les redirections
// Restore les FD si close_backups est true
void	close_fds(t_cmd *cmds, bool close_backups)
{
	if (cmds->io_fds)
	{
		if (cmds->io_fds->fd_in != -1)
			close(cmds->io_fds->fd_in);
		if (cmds->io_fds->fd_out != -1)
			close(cmds->io_fds->fd_out);
		if (close_backups)
			io_restorer(cmds->io_fds);
	}
	close_pipe_fds(cmds, NULL);
}

// Libère les ressources structs io_fds
// Restore les FD des fichiers standards & ferme les fichiers temp de l'heredoc
void	free_io(t_io_fds *io)
{
	if (!io)
		return ;
	io_restorer(io);
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

// Libere les ressources d'un **tableau donné
void	free_tab(char **tab)
{
	int	i;

	i = -1;
	if (tab)
	{
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
}

// Un free universel pour tout les pointeurs alloués
void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}
