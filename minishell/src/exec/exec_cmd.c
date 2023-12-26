/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:36:44 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/26 08:50:20 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_builtin(t_data *data, t_cmd *cmd)
{
	int	ret;

	ret = CMD_NOT_FOUND;
	if (ft_strncmp(cmd->command, "cd", 3) == SUCCESS)
		ret = builtin_cd(data, cmd->args);
	else if (ft_strncmp(cmd->command, "echo", 5) == SUCCESS)
		ret = builtin_echo(cmd->args);
	else if (ft_strncmp(cmd->command, "env", 4) == SUCCESS)
		ret = builtin_env(data, cmd->args);
	else if (ft_strncmp(cmd->command, "export", 7) == SUCCESS)
		ret = builtin_export(data, cmd->args);
	else if (ft_strncmp(cmd->command, "pwd", 4) == SUCCESS)
		ret = builtin_pwd(data);
	else if (ft_strncmp(cmd->command, "unset", 6) == SUCCESS)
		ret = builtin_unset(data, cmd->args);
	else if (ft_strncmp(cmd->command, "exit", 5) == SUCCESS)
		ret = builtin_exit(data, cmd->args);
	return (ret);
}

static int	execute_system(t_data *data, t_cmd *cmd)
{
	if (!cmd->command || cmd->command[0] == '\0')
		return (CMD_NOT_FOUND);
	if (cmd_is_dir(cmd->command))
		return (CMD_NOT_FOUND);
	cmd->path = parse_cmd_path(data, cmd->command);
	if (!cmd->path)
		return (CMD_NOT_FOUND);
	if (execve(cmd->path, cmd->args, data->env) == -1)
		errmsg_cmd("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

static int	execute_local(t_data *data, t_cmd *cmd)
{
	int	ret;

	ret = check_cmd_not_found(data, cmd);
	if (ret != 0)
		return (ret);
	if (execve(cmd->command, cmd->args, data->env) == -1)
		return (errmsg_cmd("execve", NULL, strerror(errno), errno));
	return (EXIT_FAILURE);
}

int	execute_command(t_data *data, t_cmd *cmd)
{
	int	ret;

	if (!cmd || !cmd->command)
		exit_shell(data, errmsg_cmd("child", NULL,
				"parsing error: no command to execute!", EXIT_FAILURE));
	if (!check_if_of(cmd->io_fds))
		exit_shell(data, EXIT_FAILURE);
	set_pipe_fds(data->cmd, cmd);
	io_redirecter(cmd->io_fds);
	close_fds(data->cmd, false);
	if (ft_strchr(cmd->command, '/') == NULL)
	{
		ret = execute_builtin(data, cmd);
		if (ret != CMD_NOT_FOUND)
			exit_shell(data, ret);
		ret = execute_system(data, cmd);
		if (ret != CMD_NOT_FOUND)
			exit_shell(data, ret);
	}
	ret = execute_local(data, cmd);
	exit_shell(data, ret);
	return (ret);
}
