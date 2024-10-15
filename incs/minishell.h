#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include "readline/history.h"
# include "readline/readline.h"
# include "struct.h"

// set_command_tab.c
int		set_command_tab(t_mini *shell);

// handle_redirection.c
t_bool	handle_output(t_token *token, t_cmd *cmd, int i);

t_bool	handle_input(t_token *token, t_cmd *cmd, int i);

t_bool	handle_heredoc(t_mini *shell, t_token *token, t_cmd *cmd, int i);

// env.c
char	*get_env_value(t_mini *shell, char *str, int malloc);

// init.c
t_bool	init_shell(t_mini *shell, int first_time, char **envp);

void	init_cmd(t_cmd *cmd);

// token_utils.c
t_bool	second_pass(t_mini *shell);

// token.c
t_bool	set_token(t_mini *shell);

// expand.c
char	*expand_env(t_mini *shell, char *str);

// free.c
t_bool	ft_error(char *error);

void	free_tab(char **tab);

void	free_token(t_token *token, int tlen);

t_bool	ft_free(t_mini *shell, char *error, int flag);

// signal.c
void	signal_handler(void);

// debug.c
void	print_token(t_mini *shell);

void	print_cmd(t_mini *shell);

#endif