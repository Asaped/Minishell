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

# include <stdio.h>
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
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

///////////////////////////////////////COMMAND/////////////////////////////////////////////////////

// set_command_tab.c
int		set_command_tab(t_mini *shell);

// handle_redirection.c
int		handle_output(t_token *token, t_cmd *cmd, int i);
int		handle_input(t_token *token, t_cmd *cmd, int i);
int		handle_heredoc(t_mini *shell, t_token *token, t_cmd *cmd, int i);

// cmd_utils.c
int		set_heredoc2(t_mini *shell, t_cmd *cmd, char *str, int fd);
void	get_command2(t_cmd *cmd, t_token *token, int *i, int *j);

////////////////////////////////////ENV//////////////////////////////////////////////////////

//env.c
char	*get_env_value(t_mini *shell, char *str, int malloc);
char	**set_env_var(char **env, char *key, char *value);
char	**realloc_env(char **env, int len);
int		get_env_index(char **env, char *key);

//init.c
int		init_shell(t_mini *shell, int first_time, char **envp);
void	init_cmd(t_cmd *cmd);
//void	init_fds(t_cmd *cmd);

////////////////////////////////////TOKEN//////////////////////////////////////////////////////

//token_utils.c
int		second_pass(t_mini *shell);

//token.c
int		set_token(t_mini *shell);
int		get_path_bin(char *str, char *cmd, t_token *token);

//expand.c
char	*expand_env(t_mini *shell, char *str);

////////////////////////////////////UTILS//////////////////////////////////////////////////////

//free.c
int		ft_error(char *error);
void	free_tab(char **tab);
void	free_token(t_token *token, int tlen);
int		ft_free(t_mini *shell, char *error, int flag);

//error.c
void	f_printf(int std, char *s1, char *s2, char *s3);

////////////////////////////////////SIGNAL//////////////////////////////////////////////////////

//signal.c
void	signal_handler_interactive(void);
void	handle_interactive(int sig);
void	signal_handler_interactive_heredoc(void);
void	handle_interactive_heredoc(int sig);
void	signal_handler_non_interactive(void);
void	handle_non_interactive(int sig);

////////////////////////////////////DEBUG//////////////////////////////////////////////////////

//debug.c
void	print_token(t_mini *shell);
void	print_cmd(t_mini *shell);

//void	check_dot_and_file(t_cmd *cmd);

////////////////////////////////////EXEC//////////////////////////////////////////////////////

//exec.c
void	execute_pipeline(t_mini *shell);
void	execute_command(t_cmd *cmd, char **env);
void	setup_redirections(t_cmd *cmd);
void	setup_pipes(t_cmd *cmd, int prev_fd, int is_last_cmd);
void	fork_and_execute(t_mini *shell, t_cmd *cmd, int prev_fd,
			int is_last_cmd);

//exec_utils.c
void	check_command(t_cmd *cmd);
int		check_builtin(t_mini *shell, t_cmd *cmd, int *prev_fd, int *i);

//exec_builtins.c
int		exec_builtin(t_cmd *cmd, t_mini *shell);
void	update_exit_status(int status);
void	execute_builtin(t_cmd *cmd, t_mini *shell, int *prev_fd, int i);
void	restore_stdin_stdout(int std_in, int std_out);

////////////////////////////////////BUILTINS//////////////////////////////////////////////////////

//cd.c
int		ft_cd(t_mini *shell, t_cmd *cmd);
int		ft_is_dir(char *path);

//echo.c
int		ft_echo(t_cmd *cmd);

//env.c
int		ft_env(char **env, t_cmd *cmd, int export_mode);

//exit.c
int		ft_exit(t_mini *shell, t_cmd *cmd);

//export.c
int		ft_export(t_mini *shell, t_cmd *cmd);
char	**get_key_and_value(char *str);
int		is_valid_key(char *str);

//export_no_arg.c
int count_env(char **env);
char **copy_env(char **env, int count);
void bubble_sort_env(char **env, int count);
void print_env_var(char *var);
void print_sorted_env(char **env);

// pwd.c
int		ft_pwd(void);

// unset.c
int		ft_unset(t_mini *shell, t_cmd *cmd);

//////////////////////////////////////////////////////////////////////////////////////////

#endif
