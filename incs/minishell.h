/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: nigateau <nigateau@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/01/20 21:08:03 by nigateau          #+#    #+#             */
/*   Updated: 2025/01/20 21:08:03 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include "struct.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// set_command_tab.c
int		set_command_tab(t_mini *shell);

// handle_redirection.c
t_bool	handle_output(t_token *token, t_cmd *cmd, int i);
t_bool	handle_input(t_token *token, t_cmd *cmd, int i);
t_bool	handle_heredoc(t_mini *shell, t_token *token, t_cmd *cmd, int i);

//env.c
char	*get_env_value(t_mini *shell, char *str, int malloc);

//init.c
t_bool	init_shell(t_mini *shell, int first_time, char **envp);
void	init_cmd(t_cmd *cmd);
void	init_fds(t_cmd *cmd);

//token_utils.c
t_bool	second_pass(t_mini *shell);

//token.c
t_bool	set_token(t_mini *shell);

//expand.c
char	*expand_env(t_mini *shell, char *str);

//free.c
t_bool	ft_error(char *error);
void	free_tab(char **tab);
void	free_token(t_token *token, int tlen);
t_bool	ft_free(t_mini *shell, char *error, int flag);

//signal.c
void	signal_handler_interactive(void);
void	signal_handler_non_interactive(void);

//debug.c
void	print_token(t_mini *shell);
void	print_cmd(t_mini *shell);

//exec.c
void	execute_pipeline(t_mini *shell);
void	fork_and_execute(t_mini *shell, t_cmd *cmd, int prev_fd,
			int is_last_cmd);
void	execute_command(t_cmd *cmd, char **env);
void	setup_redirections(t_cmd *cmd);
void	setup_pipes(t_cmd *cmd, int prev_fd, int is_last_cmd);
void	check_dot_and_file(t_cmd *cmd);

//exec_builtins
int		exec_builtin(t_cmd *cmd, t_mini *shell);
void	update_exit_status(int status);
void	execute_builtin(t_cmd *cmd, t_mini *shell, int *prev_fd, int i);
void	restore_stdin_stdout(int std_in, int std_out);

//cd.c
t_bool	ft_cd(t_mini *shell, t_cmd *cmd);
t_bool	ft_is_dir(char *path);

//echo.c
t_bool	ft_echo(t_cmd *cmd);

//env.c
t_bool	ft_env(char **env, t_cmd *cmd, int export_mode);

//exit.c
t_bool	ft_exit(t_mini *shell, t_cmd *cmd);

//export.c
t_bool	ft_export(t_mini *shell, t_cmd *cmd);
char	**set_env_var(char **env, char *key, char *value);
char	**realloc_env(char **env, int len);
int		get_env_index(char **env, char *key);
char	**get_key_and_value(char *str);
t_bool	is_valid_key(char *str);

// pwd.c
t_bool	ft_pwd(void);

// unset.c
t_bool	ft_unset(t_mini *shell, t_cmd *cmd);

//error.c
void	f_printf(int std, char *error_msg, char *token);

#endif