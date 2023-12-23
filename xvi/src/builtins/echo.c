/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:29:37 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:08:01 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	with_flag(char *arg)
{
	int		i;

	i = 0;
	if (arg[i++] != '-')
		return (false);
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (true);
	return (false);
}

static void	print_args(char **args, bool flag, int i)
{
	if (!args[i])
	{
		if (!flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!args[i + 1] && !flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	return ;
}

int	builtin_echo(char **args)
{
	bool	flag;
	int		i;

	flag = false;
	i = 1;
	while (args[i] && with_flag(args[i]))
	{
		flag = true;
		i++;
	}
	print_args(args, flag, i);
	return (EXIT_SUCCESS);
}
