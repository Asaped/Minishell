/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:25:10 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 11:53:43 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Verifie si le flag -n est présent
static bool	has_flag(char *arg)
{
	if (ft_strcmp(arg, "-n") == SUCCESS)
		return (true);
	else
		return (false);
}

// Ecris sur la sortie standard les arguments passés a la commande echo
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

// Fonction principale 
// Verifie seulement si le 1er arg est le flag -n, et envoi les
// arguments a partir de du 2eme si c'est le cas
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
