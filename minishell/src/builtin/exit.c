/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:28:06 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 11:55:36 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//	Vérifie si la valeur de sortie est dans la plage acceptable pour un 'long'
//	Si la valeur est hors plage, elle affecte 'true' à 'error'
//	Utilisé pour gérer si la valeur de sortie est trop grande
static bool	check_out_of_range(int neg, unsigned long long num, bool *error)
{
	if ((neg == 1 && num > LONG_MAX) || (neg == -1
			&& num >= (unsigned long)LONG_MIN))
		*error = true;
	return (*error);
}

// Pareil qu'un atoi, mais en unsigned long long
static int	ft_atol(const char *str, bool *error)
{
	unsigned long long	num;
	int					neg;
	int					i;

	num = 0;
	neg = 1;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		if (check_out_of_range(neg, num, error))
			break ;
		i++;
	}
	return (num * neg);
}

//	Récupère le code de sortie.
//	Gère les cas spéciaux comme 'OLDPWD' non défini ou les arguments numériques
//	'error' indique si une erreur s'est produite lors de la récupération du code
static int	get_exit_code(char *arg, bool *error)
{
	unsigned long long	i;

	if (!arg)
		return (g_exit_status);
	i = 0;
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
		if (!isdigit(arg[i]) && !ft_isspace(arg[i]))
			*error = true;
		i++;
	}
	i = ft_atol(arg, error);
	return (i % 256);
}

//	Détermine si la commande 'exit' silencieuse.
//	Si 'exit' fait partie d'un pipeline de commandes = quiet
static bool	is_quiet(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	if (!cmd)
		return (false);
	if (cmd->next != NULL || cmd->prev != NULL)
		return (true);
	return (false);
}

//	Nettoie et libere les ressources avant de quitter le shell
int	builtin_exit(t_data *data, char **args)
{
	int		exit_code;
	bool	error;
	bool	quiet;

	quiet = is_quiet(data);
	error = false;
	if (!quiet)
		ft_putendl_fd("exit", ERROR);
	if (!args || !args[1])
		exit_code = g_exit_status;
	else
	{
		exit_code = get_exit_code(args[1], &error);
		if (error)
			exit_code = errmsg_cmd("exit", args[1], "numeric argument required",
					ERROR);
		else if (args[2])
			return (errmsg_cmd("exit", NULL, "too many arguments", FAILURE));
	}
	exit_shell(data, exit_code);
	return (ERROR);
}
