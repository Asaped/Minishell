/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:20:11 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/25 15:03:23 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ----------------------------- STD LIBS ----------------------------------- */
# include <stdio.h>
# include <termios.h>
# include <curses.h>
# include <dirent.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include "readline/readline.h"
# include "readline/history.h"
/* ---------------------------- PERSO LIBS ---------------------------------- */
# include "libft/libft.h"
# include "gnl/get_next_line.h"

/* ------------------------------ COLORS ------------------------------------ */
# define RST	"\033[0m"
# define R		"\033[1;31m"
# define G		"\033[1;32m"
# define Y		"\033[1;33m"
# define B		"\033[1;34m"
# define M		"\033[1;35m"
# define C		"\033[1;36m"
# define W		"\033[1;37m"

/* ------------------------------ MACROS ------------------------------------ */
# define HEREDOC_NAME "/tmp/.msh_hdc_"
# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126
# define SUCCESS 0
# define FAILURE 1
# define PROMPT "[" R "Minishell" RST "] " Y " $> " RST

/* -------------------------- GLOBAL_VARIABLE ------------------------------- */
extern int	g_exit_status;

/* ----------------------------- STRUCTS ------------------------------------ */
typedef struct s_token
{
	char			*str;
	char			*str_copy;
	bool			var_exists;
	int				type;
	int				status;
	bool			join;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_io_fds
{
	char	*infile;
	char	*outfile;
	char	*hdc_delimiter;
	bool	hdc_quotes;
	int		fd_in;
	int		fd_out;
	int		stdin_copy;
	int		stdout_copy;
}	t_io_fds;

typedef struct s_cmd
{
	char			*command;
	char			*path;
	char			**args;
	bool			pipe_output;
	int				*pipe_fd;
	t_io_fds		*io_fds;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_data
{
	t_token	*token;
	char	*user_input;
	char	**env;
	char	*wdir;
	char	*old_wdir;
	t_cmd	*cmd;
	pid_t	pid;
}	t_data;

/* ------------------------------- ENUMS ------------------------------------ */
enum e_token_types {
	SPACES = 1,
	WORD,
	VAR,
	PIPE,
	INPUT,
	TRUNC,
	HEREDOC,
	APPEND,
	END
};

enum e_quoting_status {
	DEFAULT,
	SQ,
	DQ
};

/* ----------------------------- FUNCTIONS ---------------------------------- */
bool	init_data(t_data *data, char **env);
void	init_io(t_cmd *cmd);
void	exit_shell(t_data *data, int exno);
int		errmsg_cmd(char *cmd, char *detail, char *err_msg, int err_nb);
void	errmsg(char *errmsg, char *detail, int quotes);
void	free_data(t_data *data, bool clear_history);
void	close_fds(t_cmd *cmds, bool close_backups);
void	free_io(t_io_fds *io);
void	free_ptr(void *ptr);
void	free_tab(char **tab);
bool	parse_user_input(t_data *data);
int		tokenization(t_data *data, char *str);
int		save_word_or_sep(int *i, char *str, int start, t_data *data);
int		set_status(int status, char *str, int i);
int		is_separator(char *str, int i);
int		save_word(t_token **token_lst, char *str, int index, int start);
int		save_separator(t_token **token_lst, char *str, int index, int type);
int		check_consecutives(t_token **token_lst);
int		check_if_var(t_token **token_lst);
t_token	*create_token(char *str, char *str_copy, int type, int status);
void	add_token(t_token **alst, t_token *new_node);
void	delete_token(t_token *lst, void (*del)(void *));
void	clear_tokens(t_token **lst, void (*del)(void *));
t_token	*insert_token(t_token **head, t_token *to_del, t_token *insert);
int		var_expander(t_data *data, t_token **token_lst);
char	*var_recover(t_token *token, char *str, t_data *data);
char	*var_identifier(char *str);
int		var_len(char *str);
bool	is_valid_char(char c);
int		var_replacer(t_token **token_node, char *var_value, int index);
void	var_copy_val(char *new_str, char *var_value, int *j);
char	*var_expand_hdc(t_data *data, char *str);
char	*replace_str_heredoc(char *str, char *var_value, int index);
char	*get_new_token_string(char *old, char *var_val, int new_len, int index);
int		quotes_handler(t_data *data);
bool	has_quote(char *str);
int		count_len(char *str, int count, int i);
int		quotes_remover(t_token **token_node);
void	create_commands(t_data *data, t_token *token);
void	parse_word(t_cmd **cmd, t_token **token_lst);
int		fill_args(t_token	**token_node, t_cmd *last_cmd);
int		add_args_def(t_token **token_node, t_cmd *last_cmd);
int		create_args_def(t_token **token_node, t_cmd *last_cmd);
int		add_args_echo(t_token **token_node, t_cmd *last_cmd);
int		create_args_echo(t_token **token_node, t_cmd *last_cmd);
char	*var_joiner(t_token **token_node);
int		args_counter(t_token *temp);
char	**tab_duplicate(int len, char **tab, t_cmd *last, t_token *tmp);
void	var_remover_empty(t_token **tokens);
t_cmd	*cmd_creator(bool value);
void	cmd_adder(t_cmd **alst, t_cmd *new_node);
t_cmd	*last_cmd(t_cmd *cmd);
void	cmd_remover(t_cmd *lst, void (*del)(void *));
void	cmds_clear(t_cmd **lst, void (*del)(void *));
void	parse_trunc(t_cmd **last_cmd, t_token **token_lst);
char	*get_rel_path(char *file_to_open);
bool	remove_old_file_ref(t_io_fds *io, bool infile);
void	parse_input(t_cmd **last_cmd, t_token **token_lst);
void	parse_append(t_cmd **last_cmd, t_token **token_lst);
void	parse_heredoc(t_data *data, t_cmd **last_cmd, t_token **token_lst);
bool	fill_heredoc(t_data *data, t_io_fds *io, int fd);
void	parse_pipe(t_cmd **cmd, t_token **token_lst);
int		env_var_count(char **env);
int		venv_index(char **env, char *var);
char	*venv_value(char **env, char *var);
bool	is_valid_venv_key(char *var);
bool	venv_set(t_data *data, char *key, char *value);
bool	venv_delete(t_data *data, int idx);
int		builtin_env(t_data *data, char **args);
int		builtin_pwd(t_data *data, char **args);
int		builtin_echo(t_data *data, char **args);
int		builtin_export(t_data *data, char **args);
int		builtin_unset(t_data *data, char **args);
int		builtin_cd(t_data *data, char **args);
int		builtin_exit(t_data *data, char **args);
void	ignore_sigquit(void);
void	signals_on(void);
void	signals_off(void);
int		execute(t_data *data);
int		execute_command(t_data *data, t_cmd *cmd);
int		execute_builtin(t_data *data, t_cmd *cmd);
bool	cmd_is_dir(char *cmd);
int		check_cmd_not_found(t_data *data, t_cmd *cmd);
char	*parse_cmd_path(t_data *data, char *cmd);
bool	create_pipes(t_data *data);
bool	set_pipe_fds(t_cmd *cmds, t_cmd *curr_cmd);
void	close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd);
bool	check_if_of(t_io_fds *io);
bool	redirect_io(t_io_fds *io);
bool	restore_io(t_io_fds *io);
bool	get_heredoc(t_data *data, t_io_fds *io);
char	*get_prompt(t_data *data);

#endif
