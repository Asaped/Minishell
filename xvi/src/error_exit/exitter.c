/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:27:47 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:07:14 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_shell(t_data *data, int exit_status)
{
	if (data)
	{
		if (data->cmd && data->cmd->io_fds)
			close_fds(data->cmd, true);
		free_data(data, true);
	}
	exit(exit_status);
}
