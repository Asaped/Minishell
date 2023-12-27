/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:25:10 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/27 14:55:34 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	has_flag(char *arg)
{
	if (ft_strcmp(arg, "-n") == SUCCESS)
		return (true);
	else
		return (false);
}

static void	print_args_echo(char **args, bool flag_n, int i)
{
	if (!args[i])
	{
		if (!flag_n)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!args[i + 1] && !flag_n)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

int	builtin_echo(char **args)
{
	int		i;
	bool	flag_n;

	flag_n = false;
	i = 1;
	while (args[i] && has_flag(args[i]))
	{
		flag_n = true;
		i++;
	}
	print_args_echo(args, flag_n, i);
	return (EXIT_SUCCESS);
}
