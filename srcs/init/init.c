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

static int	is_unclosed_quote(char *str)
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
				return (1);
			i++;
		}
	}
	return (0);
}

static int	check_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '|')
		return (0);
	//a gérer à 42
	i = ft_strlen(str) - 1;
	while (i >= 0 && str[i] == ' ')
		i--;
	if (str[i] == '|')
		return (0);
	return (1);
}


int	init_shell(t_mini *shell, char *input)
{
	shell->tlen = count_word(input, 0 , 0);
	if (shell->tlen < 1)
		return (0);
	else if (is_unclosed_quote(input))
		return (ft_error(1));
	else if (!check_pipe(input))
		return (ft_error(2));
	shell->input = input;
	shell->token = malloc(sizeof(t_token) * shell->tlen);
	return (1);
}