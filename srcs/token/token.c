#include "../../incs/minishell.h"

static t_type	find_token_type(char *str)
{
	if (is_cmd(str))
		return (CMD);
	else if (is_op(str[0]) && (!is_op(str[1]) || (is_op(str[1]) && str[1] != '|' && str[0] != '|')))
		return (OPERATOR);
	else if (str[0] == '-' && str[1] == 'n' && !str[2])
		return (OPTIONN);
	else if (is_quote(str[0]) && is_quote(str[ft_strlen(str) - 1]))
		return (STRING);
	else if (is_file(str) || !access(str, F_OK))
		return (DIR);
	else
		return (UNKNOWN);
}

static void	create_token(t_mini *shell, int j, int i)
{
	char	*str;
	int		len;
	
	len = wordlen(shell->input, j);
	str = worddup(shell->input, j, len);
	shell->token[i].pos = j;
	shell->token[i].type = find_token_type(str);
	if (shell->token[i].type == OPTIONN)
		shell->token[i].value = NULL;
	else
		shell->token[i].value = str;
}

static int	find_cmd(t_token *token, int i)
{
	while (token[i].type != OPERATOR && i >= 0)
		i--;
	if (i == -1 || (token[i].value[0] == '|' && token[i].type == OPERATOR))
		i++;
	if (token[i].type == CMD || (token[i].type == OPERATOR && token[i].value[0] != '|'))
		return (1);
	return (0);
}

static void	second_pass(t_mini *shell)
{
	int	i;

	i = -1;
	while (++i < shell->tlen)
	{
		if (shell->token[i].type == UNKNOWN)
		{
			if (find_cmd(shell->token, i))
				shell->token[i].type = STRING;
		}
	}
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
			create_token(shell, j, i++);
		while (shell->input[j] && shell->input[j] != ' ' && !is_op(shell->input[j]) && !is_quote(shell->input[j]))
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
}