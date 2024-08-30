#include "../../incs/minishell.h"

static t_bool	find_cmd(t_mini *shell, char *path_bin, char *cmd, int j)
{
	char	**tab;
	char	*tmp;
	int		len;
	int		i;

	tab = ft_split(path_bin, ':');
	len = ft_tablen(tab);
	i = -1;
	while (++i < len)
	{
		tab[i] = ft_strjoin2(tab[i], '/');
		tmp = ft_strjoin3(tab[i], cmd);
		if (access(tmp, X_OK) == 0)
		{
			shell->token[j].path_bin = tmp;
			free_tab(tab);
			return (TRUE);
		}
	}
	if (tab)
		free_tab(tab);
	return (FALSE);
}

static t_type	find_token_type(t_mini *shell, char *str, int i)
{
	if (find_cmd(shell, get_env_value(shell, "PATH"), str, i))
		return (CMD);
	else if (is_builtin(str))
		return (BUILTIN);
	else if (is_op(str[0]) && (!is_op(str[1]) || (is_op(str[1]) && str[1] != '|' && str[0] != '|')))
		return (OPERATOR);
	else if (str[0] == '-' && str[1] == 'n' && !str[2])
		return (OPTIONN);
	else if (is_quote(str[0]) && is_quote(str[ft_strlen(str) - 1]))
		return (STRING);
	else if (is_file(str))
		return (FICHIER);
	else if (str[0] == '$' && str[1])
		return ($);
	else
		return (UNKNOWN);
}

static void	create_token(t_mini *shell, int j, int i)
{
	char	*str;

	shell->token[i].path_bin = NULL;
	shell->token[i].len = wordlen(shell->input, j);
	str = worddup(shell->input, j, shell->token[i].len);
	shell->token[i].original_pos = j;
	shell->token[i].type = find_token_type(shell, str, i);
	if (shell->token[i].type == OPTIONN)
		shell->token[i].value = NULL;
	else
		shell->token[i].value = str;
}

static t_bool	find_first_token(t_token *token, int i)
{
	while (token[i].type != OPERATOR && i >= 0)
		i--;
	if (i == -1 || (token[i].value[0] == '|' && token[i].type == OPERATOR))
		i++;
	if (token[i].type == CMD || token[i].type == BUILTIN || token[i].type == $ || (token[i].type == OPERATOR && token[i].value[0] != '|'))
		return (TRUE);
	return (FALSE);
}

static void	second_pass(t_mini *shell)
{
	int	i;

	i = -1;
	while (++i < shell->tlen)
	{
		if (shell->token[i].type == UNKNOWN)
		{
			if (find_first_token(shell->token, i))
				shell->token[i].type = STRING;
		}
	}
}

static void	expand(t_mini *shell)
{
	int		i;
	char	*tmp;

	i = -1;
	while (++i < shell->tlen)
	{
		if (shell->token[i].type == $)
		{
			tmp = ft_strdup(get_env_value(shell, shell->token[i].value + 1));
			free(shell->token[i].value);
			if (tmp)
				shell->token[i].value = tmp;
		}
	}
}

static int	find_next_operator(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i + j] && !is_op(str[i + j]))
		j++;
	return (j);
}

static t_token	token_dup(t_mini *shell, int i, int cmd)
{
	t_token	token;

	token.path_bin = NULL;
	token.type = shell->token[i].type;
	token.original_pos = shell->token[i].original_pos;
	token.len = shell->token[i].len;
	if (cmd)
	{
		token.path_bin = ft_strdup(shell->token[i].path_bin);
		token.value = worddup(shell->input, shell->token[i].original_pos, find_next_operator(shell->input, shell->token[i].original_pos));
	}
	else
		token.value = ft_strdup(shell->token[i].value);
	return (token);
}

static void	rearrange_token(t_mini *shell)
{
	t_token	*token;
	int	len;
	int	i;
	int	j;
	int	trigger;

	len = shell->tlen;
	i = -1;
	trigger = 0;
	while (++i < len)
	{
		if (shell->token[i].type == CMD)
			trigger = 1;
		else if (shell->token[i].type == OPERATOR && trigger == 1)
			trigger = 0;
		else if (trigger == 1)
			shell->tlen--;
	}
	token = malloc(sizeof(t_token) * shell->tlen);
	i = -1;
	trigger = 0;
	j = 0;
	while (++i < len)
	{
		if (shell->token[i].type == CMD)
		{
			trigger = 1;
			token[j++] = token_dup(shell, i, 1);
		}
		else if (shell->token[i].type == OPERATOR && trigger == 1)
			trigger = 0;
		if (trigger == 0)
			token[j++] = token_dup(shell, i, 0);
	}
	free_token(shell->token, len);
	shell->token = token;
}

void	tokenize(t_mini *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < shell->tlen)
	{
		while (shell->input[j] && shell->input[j] == ' ')
			j++;
		if (shell->input[j] && !is_quote(shell->input[j]) && !is_op(shell->input[j]))
			create_token(shell, j++, i++);
		while (shell->input[j] && shell->input[j] != ' ' && shell->input[j] != '$' && !is_op(shell->input[j]) && !is_quote(shell->input[j]))
			j++;
		if (is_quote(shell->input[j]) || is_op(shell->input[j]))
		{
			create_token(shell, j++, i++);
			if (is_op(shell->input[j]))
				j++;
			else if (is_quote(shell->input[j - 1]))
				j += skip_quote(shell->input, j);
		}
	}
	second_pass(shell);
	expand(shell);
	rearrange_token(shell);
}