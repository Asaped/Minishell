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
	int	pos;

	i = -1;
	pos = 0;
	while (++i < ft_strlen(str))
	{
		while (str[i] && !is_quote(str[i]))
			i++;
		if (is_quote(str[i]))
			pos = i++;
		while (str[i] && str[i] != str[pos])
			i++;
		if (str[i] != str[pos] && is_quote(str[pos]))
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
	while (shell->input[i] && shell->input[i] == ' ')
		i++;
	if (shell->input[i] == '|')
		return (FALSE);
	i = ft_strlen(shell->input) - 1;
	while (i >= 0 && shell->input[i] == ' ')
		i--;
	if (shell->input[i] == '|')
		redisplay_prompt(shell, 1);
	return (TRUE);
}

t_bool	init_shell(t_mini *shell)
{
	shell->tlen = count_word(shell->input, 0 , 0);
	if (shell->tlen < 1)
		return (FALSE);
	getcwd(shell->path, 4096);
	if (check_pipe(shell) == FALSE)
		return (ft_error(2));
	else if (is_unclosed_quote(shell->input) == TRUE)
		redisplay_prompt(shell, 2);
	shell->tlen = count_word(shell->input, 0 , 0);
	if (shell->tlen < 1)
		return (FALSE);
	shell->token = malloc(sizeof(t_token) * shell->tlen);
	if (!shell->token)
		return (ft_error(3));
	return (TRUE);
}