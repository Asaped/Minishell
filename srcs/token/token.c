/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:23:00 by nigateau          #+#    #+#             */
/*   Updated: 2025/01/20 20:23:00 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static t_bool	get_path_bin(char *str, char *cmd, t_token *token)
{
	char	*tmp;

	str = ft_strjoin2(str, '/');
	if (!str)
		return (ft_error(strerror(errno)));
	tmp = ft_strjoin3(str, cmd);
	if (!tmp)
		return (ft_error(strerror(errno)));
	free(str);
	if (access(tmp, F_OK) == 0 && access(tmp, X_OK) == 0)
	{
		token->path_bin = tmp;
		return (TRUE);
	}
	else
		free(tmp);
	return (FALSE);
}

static t_bool	find_cmd(t_mini *shell, char *path_bin, char *cmd, int j)
{
	char	**tab;
	int		len;
	int		i;

	if (!path_bin || !cmd || ft_strlen(cmd) < 1)
		return (FALSE);
	tab = ft_split(path_bin, ':');
	if (!tab)
		return (ft_error(strerror(errno)));
	len = ft_tablen(tab);
	i = -1;
	while (ft_strchr(cmd, '/') == NULL && ++i < len)
		get_path_bin(tab[i], cmd, &shell->token[j]);
	if (tab)
		free(tab);
	if (shell->token[j].path_bin != NULL)
		return (TRUE);
	else if (cmd[0] == '/' && cmd[1] && access(cmd, F_OK) != -1)
		shell->token[j].path_bin = ft_strdup(cmd);
	else if (cmd[0] == '.' && cmd[1] == '/' && cmd[2] && access(cmd + 2,
			F_OK) != -1)
		shell->token[j].path_bin = ft_strjoin3(shell->path, cmd + 1);
	else if (access(cmd, F_OK) != -1)
		shell->token[j].path_bin = ft_strjoin4(shell->path, ft_strjoin3("/",
					cmd));
	if (shell->token[j].path_bin != NULL)
		return (TRUE);
	return (FALSE);
}

static t_type	find_token_type(t_mini *shell, char *str, int i, char c)
{
	if (is_builtin(str))
		return (BUILTIN);
	else if (find_cmd(shell, get_env_value(shell, "PATH", 0), str, i))
		return (CMD);
	else if (c == '\'' || c == '\"')
		return (STRING);
	else if ((is_op(str[0]) && !is_op(str[1])) || (is_op(str[0])
			&& is_op(str[1]) && str[1] != '|'))
		return (OPERATOR);
	else
		return (UNKNOWN);
}

static t_bool	create_token(t_mini *shell, int j, int i)
{
	char	*str;

	shell->token[i].path_bin = NULL;
	if ((shell->input[j] == '\"' && shell->input[j + 1] == '\"')
		|| (shell->input[j] == '\'' && shell->input[j + 1] == '\''))
		j += 2;
	str = worddup(shell->input, j, wordlen(shell->input, j));
	if (!str)
		return (ft_error(strerror(errno)), ft_error("\n"));
	if (shell->input[j] != '\'' && !is_heredoc(shell->token[i - 1]))
		str = expand_env(shell, str);
	shell->token[i].len = ft_strlen(str);
	shell->token[i].type = find_token_type(shell, str, i, shell->input[j]);
	if (shell->token[i].type == CMD && !shell->token[i].path_bin)
	{
		shell->token[i].path_bin = ft_strdup(str);
		if (!shell->token[i].path_bin)
			return (ft_error(strerror(errno)));
	}
	shell->token[i].value = str;
	return (TRUE);
}

t_bool	set_token(t_mini *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < shell->tlen)
	{
		while (is_whitespace(shell->input[j]))
			j++;
		if (shell->input[j])
			if (create_token(shell, j, i++) == FALSE)
				return (FALSE);
		if (shell->input[j] && !is_whitespace(shell->input[j])
			&& !is_op(shell->input[j]) && !is_quote(shell->input[j]))
			while (shell->input[j] && !is_whitespace(shell->input[j])
				&& !is_op(shell->input[j]) && !is_quote(shell->input[j]))
				j++;
		else if (is_quote(shell->input[j]))
			j += skip_quote(shell->input, j);
		else if (is_op(shell->input[j]))
			j += skip_op(shell->input, j);
	}
	if (second_pass(shell) == FALSE)
		return (FALSE);
	return (TRUE);
}
