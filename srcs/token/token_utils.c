/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: nigateau <nigateau@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/01/20 20:16:24 by nigateau          #+#    #+#             */
/*   Updated: 2025/01/20 20:16:24 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	find_first_token(t_token *token, int i, int original_pos)
{
	while (i >= 0 && !is_pipe(token[i]))
		i--;
	if (i == -1 || is_pipe(token[i]))
		i++;
	if (token[i].type == CMD || token[i].type == BUILTIN)
		return (TRUE);
	if (token[i].type == OPERATOR)
	{
		i = original_pos;
		while (i >= 0 && token[i].type != OPERATOR)
		{
			i--;
			if ((token[i].type == CMD || token[i].type == BUILTIN) && token[i
					- 1].type != OPERATOR && token[i - 1].value[0] != '|')
				return (TRUE);
		}
		if (token[i].type == OPERATOR && token[i].value[0] != '|')
		{
			i = original_pos;
			if (token[i - 1].type == OPERATOR && token[i - 1].value[0] != '|')
				return (TRUE);
		}
	}
	return (FALSE);
}

static int	check_operator(t_token *token, int i, int tlen)
{
	if (token[i].type == OPERATOR)
	{
		if ((i == 0 && is_pipe(token[i])) || (i == tlen - 1
				&& token[i].type == OPERATOR) || (token[i].value[0] == '|'
				&& token[i - 1].type == OPERATOR)
			|| (token[i].type == OPERATOR && token[i].value[0] != '|'
				&& token[i - 1].type == OPERATOR && token[i - 1].value[0]
				!= '|'))
			return (f_printf(STDERR_FILENO,
					"bash: syntax error near unexpected token `",
					token[i].value, "'"), FALSE);
	}
	return (TRUE);
}

int	second_pass(t_mini *shell)
{
	int	i;

	i = -1;
	while (++i < shell->tlen)
	{
		if (shell->token[i].type == OPERATOR)
			if (!check_operator(shell->token, i, shell->tlen))
				return (FALSE);
		if (shell->token[i].type == UNKNOWN)
		{
			if (find_first_token(shell->token, i, i) == TRUE)
				shell->token[i].type = STRING;
		}
	}
	return (TRUE);
}

int	get_path_bin(char *str, char *cmd, t_token *token)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = ft_strjoin3(str, "/");
	if (!str)
		return (ft_error(strerror(errno)));
	tmp = ft_strjoin5(tmp2, cmd);
	if (!tmp)
		return (ft_error(strerror(errno)));
	if (access(tmp, F_OK) == 0 && access(tmp, X_OK) == 0)
	{
		token->path_bin = tmp;
		return (TRUE);
	}
	else
		free(tmp);
	return (FALSE);
}

void	find_cmd2(t_mini *shell, char *cmd, int j)
{
	if (cmd[0] == '/' && cmd[1] && access(cmd, F_OK) != -1)
		shell->token[j].path_bin = ft_strdup(cmd);
	else if (cmd[0] == '.' && cmd[1] == '/' && cmd[2] && access(cmd + 2,
			F_OK) != -1)
		shell->token[j].path_bin = ft_strjoin3(shell->path, cmd + 1);
	else if (access(cmd, F_OK) != -1)
		shell->token[j].path_bin = ft_strjoin4(shell->path, ft_strjoin3("/",
					cmd));
}
