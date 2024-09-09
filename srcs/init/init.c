#include "../../incs/minishell.h"

static int	count_word(char *str, int i, int count)
{
	while (str[i])
	{
		while (is_whitespace(str[i]))
			i++;
		if (str[i] && !is_whitespace(str[i]) && !is_op(str[i]) && !is_quote(str[i]))
			while (str[i] && !is_whitespace(str[i]) && !is_op(str[i]) && !is_quote(str[i]))
				i++;
		else if (is_quote(str[i]))
			i += skip_quote(str, i);
		else if (is_op(str[i]))
			if (is_op(str[++i]))
				i++;
		count++;
	}
	return (count);
}

static t_bool	is_unclosed_quote(char *str)
{
	int	i;
	int	pos;

	i = -1;
	while (++i < ft_strlen(str))
	{
		pos = -1;
		while (str[i] && !is_quote(str[i]))
			i++;
		if (is_quote(str[i]))
			pos = i++;
		while (str[i] && str[i] != str[pos])
			i++;
		if (pos != -1 && str[i] != str[pos] && is_quote(str[pos]))
			return (TRUE);
	}
	return (FALSE);
}

static void	redisplay_prompt(t_mini *shell, int mode)
{
	char	*input;

	while (1)
	{
		if (mode == 1)
		{
			input = readline("> ");
			if (count_word(input, 0, 0) > 0)
				break;
		}
		else if (mode == 2)
		{
			shell->input = ft_strjoin2(shell->input, '\n');
			input = readline("> ");
			shell->input = ft_strjoin(shell->input, input);
			if (is_unclosed_quote(shell->input) == FALSE)
				return ;
		}
	}
	shell->input = ft_strjoin2(shell->input, ' ');
	shell->input = ft_strjoin(shell->input, input);
}

static t_bool	check_pipe(t_mini *shell)
{
	int		i;

	i = 0;
	while (shell->input[i] && is_whitespace(shell->input[i]))
		i++;
	if (shell->input[i] == '|')
		return (FALSE);
	i = ft_strlen(shell->input) - 1;
	while (i >= 0 && is_whitespace(shell->input[i]))
		i--;
	if (shell->input[i] == '|')
		redisplay_prompt(shell, 1);
	return (TRUE);
}

/*static void	expand(t_mini *shell, char *str)
{
	int		i;
	int		j;
	int		len;
	char	tmp[4096];
	char	*tmp2;
	char	value[4096];

	i = -1;
	j = 0;
	len = ft_strlen(str);
	while (++i < len)
	{
		while (str[i] && str[i] != '$')
			tmp[j++] = str[i++];
		if (str[i] == '$' && str[i + 1] && ft_memcpy(value, shell->input + i + 1, wordlen(shell->input, i + 1)) != NULL)
		{
			tmp2 = get_env_value(shell, value);
			ft_memcpy(tmp + j, tmp2, ft_strlen(tmp2));
			printf("tmp = %s\n", tmp);
			j += ft_strlen(tmp2);
			tmp[j++] = ' ';
			i += wordlen(shell->input, i);
		}
		else
		{
			while (str[i] && !is_whitespace(str[i]) && !is_op(str[i]) && !is_quote(str[i]))
				tmp[j++] = str[i++];
		}
		printf("j and i = %d %d\n", j, i);
		printf("str[j] = %c\n", str[j - 1]);
	}
}*/

t_bool	init_shell(t_mini *shell)
{
	shell->tlen = count_word(shell->input, 0 , 0);
	if (shell->tlen < 1)
		return (FALSE);
	if (check_pipe(shell) == FALSE)
		return (ft_error("Syntax error near unexpected token \'|\'\n"));
	else if (is_unclosed_quote(shell->input) == TRUE)
		redisplay_prompt(shell, 2);
	//expand(shell, shell->input);
	shell->tlen = count_word(shell->input, 0 , 0);
	shell->token = malloc(sizeof(t_token) * (shell->tlen));
	if (!shell->token)
		return (ft_error(strerror(errno)));
	return (TRUE);
}