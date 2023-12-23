/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:01:35 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:41:05 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	check_muted(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	if (!cmd)
		return (false);
	if (cmd->next != NULL || cmd->next != NULL)
		return (true);
	return (false);
}

static long	ft_atoull(char *str)
{
	unsigned long long	res;
	int					neg;
	int					i;

	res = 0;
	neg = 1;
	i = 0;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
	{
		neg = -neg;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * neg);
}

static int	check_exit_code(char *arg, bool *error)
{
	unsigned long long	i;

	i = 0;
	if (!arg)
		return (g_exit_status);
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '\0')
		*error = true;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		*error = true;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && !ft_isspace(arg[i]))
			*error = true;
		i++;
	}
	i = ft_atoull(arg);
	return (i % 256);
}

int	builtin_exit(t_data *data, char **args)
{
	int		status;
	bool	error;
	bool	muted;

	error = false;
	muted = check_muted(data);
	if (!muted && data->interactive)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (!args || !args[1])
		status = g_exit_status;
	else
	{
		status = check_exit_code(args[1], &error);
		if (error)
			status = errmsg_cmd("exit", args[1], "numeric arg expected", 2);
		else if (args[2])
			return (errmsg_cmd("exit", NULL, "too many args", 1));
	}
	exit_shell(data, status);
	return (STDERR_FILENO);
}
