/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.lausanne>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:57:11 by nigateau          #+#    #+#             */
/*   Updated: 2025/02/16 18:53:50 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_env(char **env, t_cmd *cmd, int export_mode)
{
	int	i;
	int	len;

	i = -1;
	len = ft_tablen(env);
	if (cmd->tlen > 1)
		return (f_printf(STDERR_FILENO, "env: ", cmd->token[1],
				":No such file or directory"), TRUE);
	if (len <= 0)
	{
		return (ft_error("env: environment not set"), TRUE);
	}
	while (++i < len)
	{
		if (export_mode)
			ft_putstr_fd("export ", STDOUT_FILENO);
		ft_putendl_fd(env[i], STDOUT_FILENO);
	}
	return (FALSE);
}
