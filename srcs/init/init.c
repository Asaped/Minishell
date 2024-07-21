#include "../../incs/minishell.h"

static int	count_word(char *str, int i, int count)
{
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] && str[i] != ' ' && !is_op(str[i]) && !is_quote(str[i]))
			count++;
		while (str[i] && str[i] != ' ' && !is_quote(str[i]) && !is_op(str[i]))
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

int	init_shell(t_mini *shell, char *input)
{
	shell->tlen = count_word(input, 0 , 0);
	if (shell->tlen < 1)
		return (0);
	shell->input = input;
	shell->token = malloc(sizeof(t_token) * shell->tlen);
	return (1);
}