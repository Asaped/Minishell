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
	if (is_builtin(str))
		return (BUILTIN);
	else if (find_cmd(shell, get_env_value(shell, "PATH"), str, i))
		return (CMD);
	else if (is_op(str[0]) && (!is_op(str[1]) || (is_op(str[1]) && str[1] != '|' && str[0] != '|')))
		return (OPERATOR);
	else
		return (UNKNOWN);
}

static char	*expand_env(t_mini *shell, char *str)
{
	char	result[4096];
	char	*var;
	char	*tmp;
	int		i;
	int		j;
	int		k;
	int		len;	

	i = 0;
	j = 0;
	k = 0;
	ft_bzero(result, 4096);
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			result[j++] = str[i++];
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			len = wordlen(str, i);
			var = worddup(str, i, &len);
			tmp = get_env_value(shell, var);
			if (!tmp)
				return (NULL);
			while (tmp[k])
				result[j++] = tmp[k++];
			k = 0;
			i += wordlen(str, i);
			free(var);
		}
	}
	free(str);
	str = ft_strdup(result);
	return (str);
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
		str = expand_env(shell, str);
		shell->token[i].len = ft_strlen(str);
	}
	if (!str)
		return (ft_error("Error : Environnement variable not found\n"));
	shell->token[i].type = find_token_type(shell, str, i); 
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
				ft_error("Command not found : ");
				ft_error(shell->token[i].value);
				return (ft_error("\n"));
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