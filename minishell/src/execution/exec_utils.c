/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:11:18 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:49:01 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	check_dir_command(char *cmd)
{
	struct stat	stat_cmd;

	ft_memset(&stat_cmd, 0, sizeof(stat_cmd));
	stat(cmd, &stat_cmd);
	return (S_ISDIR(stat_cmd.st_mode));
}

int	check_not_found(t_data *data, t_cmd *cmd)
{
	if (!ft_strchr(cmd->command, '/') && venv_index(data->env, "PATH") == -1)
		return (errmsg_cmd(cmd->command, NULL, "command not found", NOT_FUND));
	if (access(cmd->command, F_OK) != SUCCESS)
		return (errmsg_cmd(cmd->command, NULL, strerror(errno), NOT_FUND));
	else if (check_dir_command(cmd->command))
		return (errmsg_cmd(cmd->command, NULL, "is a directory", NOT_EXEC));
	else if (access(cmd->command, F_OK | X_OK) != SUCCESS)
		return (errmsg_cmd(cmd->command, NULL, strerror(errno), NOT_EXEC));
	return (EXIT_SUCCESS);
}
