/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.lausanne>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:03:47 by nigateau          #+#    #+#             */
/*   Updated: 2025/02/15 20:04:21 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	is_valid_key(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i++] != '_')
		return (FALSE);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

char	**get_key_and_value(char *str)
{
	char	*pos;
	char	**tmp;

	tmp = malloc(sizeof(char *) * 3);
	if (!tmp)
		return (NULL);
	pos = ft_strchr(str, '=');
	if (pos == NULL)
	{
		tmp[0] = ft_strdup(str);
		tmp[1] = NULL;
		return (tmp);
	}
	tmp[0] = ft_substr(str, 0, pos - str);
	tmp[1] = ft_substr(pos, 1, ft_strlen(pos));
	tmp[2] = NULL;
	return (tmp);
}

int	ft_export(t_mini *shell, t_cmd *cmd)
{
	int		i;
	char	**tmp;

	if (cmd->tlen == 1)
	{
		return (print_sorted_env(shell->env), 1);
	}
	i = 0;
	while (++i < cmd->tlen)
	{
		if (!is_valid_key(cmd->token[i]))
			return (fprintf(stderr,
					"bash: export: `%s': not a valid identifier\n",
					cmd->token[i]), TRUE);
		if (cmd->token[i])
		{
			tmp = get_key_and_value(cmd->token[i]);
			shell->env = set_env_var(shell->env, tmp[0], tmp[1]);
			free_tab(tmp);
		}
	}
	return (FALSE);
}
