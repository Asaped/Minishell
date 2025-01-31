/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:27:59 by nigateau          #+#    #+#             */
/*   Updated: 2025/01/20 20:27:59 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	expand_env2(t_mini *shell, char *str, char *tmp, int *i)
{
	if (str[i[0]] == '$' && str[i[0] + 1] == '?'
		&& (is_whitespace(str[i[0] + 2]) || !str[i[0] + 2]))
	{
		i[0] += 2;
		tmp = ft_itoa(g_exit_status);
	}
	else
		tmp = get_env_value(shell,
				worddup(str, ++i[0], wordlen2(str, &i[0])), 1);
}

char	*expand_env(t_mini *shell, char *str)
{
	char	result[4096];
	char	*tmp;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	ft_bzero(result, 4096);
	while (str[i[0]])
	{
		while (str[i[0]] && str[i[0]] != '$')
			result[i[1]++] = str[i[0]++];
		if (str[i[0]] == '$' && str[i[0] + 1] && str[i[0] + 1] != '$'
			&& !is_op(str[i[0] + 1]) && !is_whitespace(str[i[0] + 1]))
		{
			expand_env2(shell, str, tmp, &i[0]);
			i[2] = 0;
			while (tmp && tmp[i[2]])
				result[i[1]++] = tmp[i[2]++];
		}
		else if (str[i[0]] == '$' || (str[i[0]] == '$' && str[i[0] + 1] == '$'))
			result[i[1]++] = str[i[0]++];
	}
	free(str);
	return (ft_strdup(result));
}
