/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.lausanne>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:56:24 by nigateau          #+#    #+#             */
/*   Updated: 2025/02/16 16:22:50 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	is_n_option(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (FALSE);
	while (str[i] && str[i] == 'n')
		i++;
	if (!str[i])
		return (TRUE);
	return (FALSE);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	is_n;

	is_n = 0;
	i = 0;
	while (++i < cmd->tlen)
	{
		if (is_n_option(cmd->token[i]) == 1)
			is_n = 1;
		if (is_n_option(cmd->token[i]) == 0)
			break ;
	}
	while (i < cmd->tlen)
	{
		ft_putstr_fd(cmd->token[i], STDOUT_FILENO);
		if (cmd->token[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!is_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (FALSE);
}
