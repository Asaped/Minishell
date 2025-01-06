#include "../../incs/minishell.h"

/*static void	exec(t_mini *shell)
{
	char	**tab;
	int	i;
	int	j;
	int	k;
	int	b;

	i = -1;
	j = 0;
	k = -1;
	b = 0;
	while (++i < shell->tlen)
	{
		if (shell->token[i].type == CMD)
		{
			while (i + j < shell->tlen && shell->token[i + j].type != OPERATOR)
				j++;
			tab = malloc(sizeof (char *) * (j + 1));
			while (++k < j)
				tab[k] = shell->token[i + b++].value;
			tab[k] = NULL;
			j++;
			//j = execve(shell->token[i].path_bin, tab, NULL);
			free(tab);
		}
	}
}*/

int g_exit_status = 0;

static t_bool	redisplay_prompt(t_mini *shell)
{
	char	*input;

	while (1)
	{
		signal_handler_interactive();
		input = readline("> ");
		signal_handler_non_interactive();
		if (input == NULL)
		{
			free(input);
			return (ft_error("bash: syntax error: unexpected end of file\n"));
		}
		input[ft_strlen(input)] = '\0';
		if (is_only_whitespace(input) == TRUE)
			shell->input = ft_strjoin(shell->input, input);
		else
		{
			shell->input = ft_strjoin(shell->input, input);
			break ;
		}
	}
	return (TRUE);
}

static t_bool	set_shell(t_mini *shell)
{
	if (check_pipe(shell->input, ft_strlen(shell->input) - 1) == TRUE)
		if (redisplay_prompt(shell) == FALSE)
			return (FALSE);
	if (is_unclosed_quote(shell->input) == TRUE)
		return (ft_error("Syntax error : unclosed quote.\n"));
	shell->tlen = count_word(shell->input, 0 , 0);
	if (shell->tlen < 1)
		return (FALSE);
	add_history(shell->input);
	shell->token = malloc(sizeof(t_token) * (shell->tlen));
	if (!shell->token)
		return (ft_error(strerror(errno)), ft_error("\n"));
	if (set_token(shell) == FALSE || set_command_tab(shell) == FALSE)
		return (FALSE);
	return (TRUE);
}

static void	minishell(t_mini *shell)
{
	g_exit_status = 0;
	while (1)
	{
		signal_handler_interactive();
		init_shell(shell, 0, NULL);
		signal_handler_non_interactive();
		shell->input = readline("minishell$ ");
		if (shell->input == NULL)
		{
			ft_free(shell, NULL, 1);
			exit(0);
		}
		shell->input[ft_strlen(shell->input)] = '\0';
		if (set_shell(shell) == FALSE)
			ft_free(shell, NULL, 0);
		else
		{
			print_token(shell);
			print_cmd(shell);
			execute_pipeline(shell);
			ft_free(shell, NULL, 0);
		}
	}
	rl_clear_history();
	ft_free(shell, NULL, 1);
}

int 	main(int ac, char **av, char **envp)
{
	t_mini	shell;
	(void)ac;
	(void)av;
	init_shell(&shell, 1, envp);
	minishell(&shell);
	return (1);
}