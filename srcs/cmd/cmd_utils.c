/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.lausanne>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:51:53 by nigateau          #+#    #+#             */
/*   Updated: 2025/02/16 16:39:46 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	set_heredoc2(t_mini *shell, t_cmd *cmd, char *str, int fd)
{
	if (str == NULL || !ft_strncmp(str, cmd->heredoc_key,
			ft_strlen(cmd->heredoc_key)))
		return (0);
	if (ft_strchr(str, '$'))
	{
		str = expand_env(shell, str);
		ft_putendl_fd(str, fd);
	}
	else
	{
		ft_putendl_fd(str, fd);
	}
	return (1);
}

void	get_command2(t_cmd *cmd, t_token *token, int *i, int *j)
{
	if (token[j[0]].path_bin != NULL && cmd->path_bin == NULL)
		cmd->path_bin = token[j[0]].path_bin;
	if (token[j[0]].type != OPERATOR)
		cmd->token[i[0]++] = token[j[0]++].value;
	if (token[j[0]].type == OPERATOR && token[j[0]].value[0] != '|')
		j[0] += 2;
}
