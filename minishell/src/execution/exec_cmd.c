/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:44:18 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:47:10 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_builtin(t_data *data, t_cmd *cmd)
{
	int	exit_status;

	exit_status = NOT_FUND;
	if (!ft_strncmp(cmd->command, "cd", 3))
		exit_status = builtin_cd(data, cmd->args);
	else if (!ft_strncmp(cmd->command, "echo", 5))
		exit_status = builtin_echo(cmd->args);
	else if (!ft_strncmp(cmd->command, "pwd", 4))
		exit_status = builtin_pwd(data);
	else if (!ft_strncmp(cmd->command, "env", 4))
		exit_status = builtin_env(data, cmd->args);
	else if (!ft_strncmp(cmd->command, "export", 7))
		exit_status = builtin_export(data, cmd->args);
	else if (!ft_strncmp(cmd->command, "unset", 6))
		exit_status = builtin_unset(data, cmd->args);
	else if (!ft_strncmp(cmd->command, "exit", 5))
		exit_status = builtin_exit(data, cmd->args);
	return (exit_status);
}

static int	exec_system(t_data *data, t_cmd *cmd)
{
	if (!cmd->command || cmd->command[0] == '\0')
		return (NOT_FUND);
	if (check_dir_command(cmd->command))
		return (NOT_FUND);
	cmd->path = get_cmd_path(data, cmd->command);
	if (!cmd->path)
		return (NOT_FUND);
	if (execve(cmd->path, cmd->args, data->env) == -1)
		errmsg_cmd("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

static int	exec_local(t_data *data, t_cmd *cmd)
{
	int	exit_status;

	exit_status = check_not_found(data, cmd);
	if (exit_status != SUCCESS)
		return (exit_status);
	if (execve(cmd->command, cmd->args, data->env) == -1)
		return (errmsg_cmd("execve", NULL, strerror(errno), errno));
	return (EXIT_FAILURE);
}

int	execute_command(t_data *data, t_cmd *cmd)
{
	int	exit_status;

	if (!cmd || !cmd->command)
		exit_shell(data, errmsg_cmd("child", NULL, "no command to execute", 1));
	if (!if_of_checker(cmd->io_fds))
		exit_shell(data, EXIT_FAILURE);
	set_pipe_fds(data->cmd, cmd);
	io_redir(cmd->io_fds);
	close_fds(data->cmd, false);
	if (!ft_strchr(cmd->command, '/'))
	{
		exit_status = exec_builtin(data, cmd);
		if (exit_status != NOT_FUND)
			exit_shell(data, exit_status);
		exit_status = exec_system(data, cmd);
		if (exit_status != NOT_FUND)
			exit_shell(data, exit_status);
	}
	exit_status = exec_local(data, cmd);
	exit_shell(data, exit_status);
	return (exit_status);
}
