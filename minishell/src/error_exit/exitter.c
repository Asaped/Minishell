/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:34:27 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 12:36:57 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Ferme le programme avec le code d'erreur donné
void	exit_shell(t_data *data, int exit_code)
{
	if (data)
	{
		if (data->cmd && data->cmd->io_fds)
			close_fds(data->cmd, true);
		free_data(data, true);
	}
	exit(exit_code);
}
