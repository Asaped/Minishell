/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:04:57 by nigateau          #+#    #+#             */
/*   Updated: 2025/01/20 21:04:59 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static char	**remove_env(char **env, int pos)
{
	int		len;
	char	*tmp;

	len = ft_tablen(env);
	while (pos < len - 1)
	{
		tmp = env[pos];
		env[pos] = env[pos + 1];
		env[++pos] = tmp;
	}
	free(env[pos]);
	env[pos] = NULL;
	env = realloc_env(env, len - 1);
	return (env);
}

int	ft_unset(t_mini *shell, t_cmd *cmd)
{
	int	i;
	int	pos;

	i = 0;
	while (++i < cmd->tlen)
	{
		pos = get_env_index(shell->env, cmd->token[i]);
		if (pos != -1)
		{
			shell->env = remove_env(shell->env, pos);
			return (FALSE);
		}
	}
	return (TRUE);
}
