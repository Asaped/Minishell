/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:32:21 by nigateau          #+#    #+#             */
/*   Updated: 2025/01/20 20:32:21 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int				g_exit_status = 0;

static char	*remove_empty_quote(char *str)
{
	int		len;
	int		i;
	int		j;
	char	result[4098];

	len = ft_strlen(str);
	i = 0;
	j = 0;
	ft_bzero(result, 4098);
	while (i < len)
	{
		while (i + 2 < len && ((is_quote(str[i]) == 1 && is_quote(str[i + 1]))
				== 1 || (is_quote(str[i]) == 2 && is_quote(str[i + 1]) == 2)))
			i += 2;
		result[j++] = str[i++];
	}
	free(str);
	str = ft_strdup(result);
	return (str);
}

static int	set_shell(t_mini *shell)
{
	if (is_unclosed_quote(shell->input) == TRUE)
		return (ft_error("Syntax error : unclosed quote."));
	add_history(shell->input);
	shell->input = remove_empty_quote(shell->input);
	shell->tlen = count_word(shell->input, 0, 0);
	if (shell->tlen < 1)
		return (FALSE);
	shell->token = malloc(sizeof(t_token) * (shell->tlen));
	if (!shell->token)
		return (ft_error(strerror(errno)));
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
		shell->input = readline("minishell$ ");
		signal_handler_non_interactive();
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
			execute_pipeline(shell);
			ft_free(shell, NULL, 0);
		}
	}
	rl_clear_history();
	ft_free(shell, NULL, 1);
}

int	main(int ac, char **av, char **envp)
{
	t_mini	shell;

	(void)ac;
	(void)av;
	init_shell(&shell, 1, envp);
	if (ac == 1)
		minishell(&shell);
	else if (ac == 3 && ft_strncmp(av[1], "-c\0", 3) == 0 && av[2])
	{
		shell.input = ft_strdup(av[2]);
		if (set_shell(&shell) == FALSE)
			ft_free(&shell, NULL, 0);
		else
		{
			execute_pipeline(&shell);
			ft_free(&shell, NULL, 1);
		}
	}
	return (1);
}
