#include "../../incs/minishell.h"

static int	count_word(char *str, int i, int count)
{
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] && str[i] != ' ' && !is_op(str[i]) && !is_quote(str[i]))
			count++;
		if (str[i] == '$')
		 i++;
		while (str[i] && str[i] != ' ' && str[i] != '$' && !is_quote(str[i]) && !is_op(str[i]))
			i++;
		if (is_quote(str[i]))
		{
			i += skip_quote(str, i);
			count++;
		}
		if (is_op(str[i]))
		{
			i++;
			count++;
			if (is_op(str[i]))
				i++;
		}
	}
	return (count);
}

static t_bool	is_unclosed_quote(char *str)
{
	int	i;
	int	quote1;
	int	quote2;

	i = 0;
	while (str[i])
	{
		while (str[i] && !is_quote(str[i]))
			i++;
		if (is_quote(str[i]))
		{
			quote1 = is_quote(str[i]);
			i += skip_quote(str, i) - 1;
			quote2 = is_quote(str[i]);
			if (quote1 != quote2)
				return (TRUE);
			i++;
		}
	}
	return (FALSE);
}

static t_bool	check_pipe(t_mini *shell)
{
	int		i;
	char	*input;

	i = 0;
	while (shell->input[i] && shell->input[i] == ' ')
		i++;
	if (shell->input[i] == '|')
		return (FALSE);
	//a gérer à 42
	i = ft_strlen(shell->input) - 1;
	while (i >= 0 && shell->input[i] == ' ')
		i--;
	if (shell->input[i] == '|')
	{
		while (1)
		{
			input = readline("> ");
			if (count_word(input, 0, 0) > 0)
				break;
		}
		shell->tlen += count_word(input, 0, 0);
		shell->input = ft_strjoin2(shell->input, ' ');
		shell->input = ft_strjoin(shell->input, input);
	}
	return (TRUE);
}

t_bool	init_shell(t_mini *shell)
{
	getcwd(shell->path, 4096);
	shell->tlen = count_word(shell->input, 0 , 0);
	if (shell->tlen < 1)
		return (FALSE);
	else if (check_pipe(shell) == FALSE)
		return (ft_error(2));
	else if (is_unclosed_quote(shell->input) == TRUE)
		return (ft_error(1));
	//else if (escape_char())
	shell->token = malloc(sizeof(t_token) * shell->tlen);
	return (TRUE);
}