#include "../../incs/minishell.h"

static t_bool	find_cmd(t_mini *shell, char *path_bin, char *cmd, int j)
{
	char	**tab;
	char	*tmp;
	int		len;
	int		i;

	if (!path_bin || !cmd || ft_strlen(cmd) < 1)
		return (FALSE);
	tab = ft_split(path_bin, ':');
	if (!tab)
		return (ft_error(strerror(errno)));
	len = ft_tablen(tab);
	i = -1;
	while (++i < len)
	{
		tab[i] = ft_strjoin2(tab[i], '/');
		if (!tab[i])
			return (ft_error(strerror(errno)));
		tmp = ft_strjoin3(tab[i], cmd);
		if (!tmp)
			return (ft_error(strerror(errno)));
		if (access(tmp, F_OK) == 0 || access(tmp, X_OK) == 0)
		{
			tmp = lower_str(tmp);
			cmd = lower_str(cmd);
			shell->token[j].path_bin = tmp;
			free_tab(tab);
			return (TRUE);
		}
		else
			free(tmp);
	}
	if (tab)
		free_tab(tab);
	return (FALSE);
}

static t_type	find_token_type(t_mini *shell, char *str, int i)
{
	(void)shell;
	(void)i;
	if (is_builtin(str))
		return (BUILTIN);
	else if ((access(str, F_OK) == 0 && access(str, X_OK) == 0) || find_cmd(shell, get_env_value(shell, "PATH"), str, i))
		return (CMD);
	else if (is_op(str[0]) && (!is_op(str[1]) || (is_op(str[1]) && str[1] != '|' && str[0] != '|')))
		return (OPERATOR);
	else
		return (UNKNOWN);
}
//à revoir
static t_bool	get_final_string(t_mini *shell, char *result, char *str, char *tmp, int *i)
{
	char	*var;

	while (str[i[0]])
	{
		while (str[i[0]] && str[i[0]] != '$')
			result[i[1]++] = str[i[0]++];
		if (str[i[0]] == '$' && str[i[0] + 1])
		{
			i[0]++;
			i[3] = wordlen(str, i[0]);
			var = worddup(str, i[0], &i[3]);
			if (!var)
				return (ft_error(strerror(errno)));
			tmp = get_env_value(shell, var);
			if (!tmp)
				return (ft_error("Error : Environnement variable not found\n"));
			while (tmp[i[2]])
				result[i[1]++] = tmp[i[2]++];
			i[2] = 0;
			i[0] += wordlen(str, i[0]);
			free(var);
		}
	}
	str = ft_strdup(result);
	return (TRUE);
}

static t_bool	expand_env(t_mini *shell, char *str)
{
	char	result[4096];
	int		i[4];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	ft_bzero(result, 4096);
	free(str);
	get_final_string(shell, result, str, NULL, i);
	if (!str)
		return (ft_error(strerror(errno)));
	return (TRUE);
}

static t_bool	create_token(t_mini *shell, int j, int i)
{
	char	*str;

	shell->token[i].path_bin = NULL;
	shell->token[i].len = wordlen(shell->input, j);
	str = worddup(shell->input, j, &shell->token[i].len);
	if (!str)
		return (ft_error(strerror(errno)));
	if (shell->input[i] != '\'')
	{
		expand_env(shell, str);
		if (!str)
			return (FALSE);
		shell->token[i].len = ft_strlen(str);
	}
	shell->token[i].type = find_token_type(shell, str, i);
	if (shell->token[i].type == CMD && !shell->token[i].path_bin)
	{
		shell->token[i].path_bin = ft_strdup(str);
		if (!shell->token[i].path_bin)
			return (ft_error(strerror(errno)));
	}
	shell->token[i].value = str;
	return (TRUE);
}

static t_bool	find_first_token(t_token *token, int i)
{
	while (i >= 0 && token[i].type != OPERATOR)
		i--;
	if (i == -1 || (token[i].value[0] == '|' && token[i].type == OPERATOR))
		i++;
	if (token[i].type == CMD || token[i].type == BUILTIN || (token[i].type == OPERATOR && token[i].value[0] != '|'))
		return (TRUE);
	return (FALSE);
}

static t_bool	second_pass(t_mini *shell)
{
	int	i;

	i = -1;
	while (++i < shell->tlen)
	{
		if (shell->token[i].type == UNKNOWN)
		{
			if (find_first_token(shell->token, i) == TRUE)
				shell->token[i].type = STRING;
			else
			{
				ft_error("minishell: ");
				ft_error(shell->token[i].value);
				if (access(shell->token[i].value, F_OK) == 0 && access(shell->token[i].value, W_OK) == -1)
					return (ft_error(": Is a directory\n"));
				else if (access(shell->token[i].value, F_OK) == 0 && access(shell->token[i].value, W_OK) == 0 && access(shell->token[i].value, X_OK) == -1)
					return (ft_error(": Permission denied\n"));
				else if (access(shell->token[i].value, F_OK) == -1)
					return (ft_error(": No such file or directory\n"));
				else
					return (ft_error(": Command not found\n"));
			}
		}
	}
	return (TRUE);
}

t_bool	tokenize(t_mini *shell)
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
		if (shell->input[j] && !is_whitespace(shell->input[j]) && !is_op(shell->input[j]) && !is_quote(shell->input[j]))
			while (shell->input[j] && !is_whitespace(shell->input[j]) && !is_op(shell->input[j]) && !is_quote(shell->input[j]))
				j++;
		else if (is_quote(shell->input[j]))
			j += skip_quote(shell->input, j);
		else if (is_op(shell->input[j]))
			if (is_op(shell->input[++j]))
				j++;
	}
	if (second_pass(shell) == FALSE)
		return (FALSE);
	//second_pass(shell);
	return (TRUE);
}