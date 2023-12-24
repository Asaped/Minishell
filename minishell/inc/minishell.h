/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 10:38:56 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/24 10:28:11 by cedmulle         ###   ########.fr       */
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
# include "readline/readline.h"
# include "readline/history.h"
/* ---------------------------- PERSO LIBS ---------------------------------- */
# include "libft/libft.h"

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
# define HDC_NAME "/tmp/.minishell_heredoc_"
# define SUCCESS 0
# define FAILURE 1
# define NOT_EXEC 126
# define NOT_FUND 127

/* ------------------------------ GLOBAL ------------------------------------ */
extern int	g_exit_status;

/* ------------------------------ ENUMS ------------------------------------- */
typedef enum e_inquote {
	DEF,
	SQ,
	DQ
}	t_inquote;

typedef enum e_type_token {
	SPACES = 1,
	WORD,
	VAR,
	PIPE,
	REDIR_OUT,
	REDIR_IN,
	HEREDOC,
	APPEND,
	END
}	t_type_token;

/* ----------------------------- STRUCTS ----------------------------------- */
typedef struct s_token
{
	char			*str;
	char			*str_copy;
	bool			exists;
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
	bool		interactive;
	t_token		*token;
	char		*user_input;
	char		**env;
	char		*wdir;
	char		*old_wdir;
	t_cmd		*cmd;
	pid_t		pid;
}	t_data;

typedef struct s_tools
{
	int	start;
	int	end;
	int	type;
}	t_tools;

/* -------------------------------------------------------------------------- */
/*                               FUNCTIONS                                    */
/* -------------------------------------------------------------------------- */
/* main.c */
void	main_minishell(t_data *data);
/* init_data.c */
bool	init_data(t_data *data, char **env);
void	init_io(t_cmd *cmd);
/* prompt.c */
char	*create_prompt(t_data *data);
/* signals.c */
void	msh_sigint(void);
void	msh_sigquit(void);
void	signals_on(void);
/* signal_utils.c */
void	handle_sigint(int sig);
void	nothing(int v);
void	backslash_n(int v);
void	sigquit_update(void);
void	sigint_update(void);
/* errors.c */
int		errmsg_cmd(char *cmd, char *detail, char *err_msg, int err_nb);
void	errmsg(char *err_msg, char *detail, int quotes);
/* cleaners.c */
void	close_fds(t_cmd *cmds, bool cl_backup);
void	free_ptr(void *ptr);
void	free_tab(char **tab);
void	free_io(t_io_fds *io);
void	free_data(t_data *data, bool history);
/* exitter.c */
void	exit_shell(t_data *data, int exit_status);
/* venv.c */
int		venv_count(char **env);
int		venv_index(char **env, char *var);
char	*venv_value(char **env, char *var);
bool	valid_venv_key(char *venv);
/* venv_setter.c */
bool	venv_set(t_data *data, char *key, char *val);
bool	venv_remover(t_data *data, int index);
/* input_output.c */
bool	io_restore(t_io_fds *io);
bool	io_redir(t_io_fds *io);
bool	if_of_checker(t_io_fds *io);
/* pipes.c */
void	close_pipe_fds(t_cmd *cmds, t_cmd *to_skip);
bool	create_pipes(t_data *data);
bool	set_pipe_fds(t_cmd *cmds, t_cmd *cmd);
/* tokenizer.c */
int		tokenizer(t_data *data, char *input);
/* token_utils.c */
t_token	*create_token(char *str, char *str_copy, int type, int status);	
void	add_token(t_token **tokens, t_token *new);
void	free_token(t_token *token, void (*del)(void *));
void	free_tokenlst(t_token **tokens, void (*del)(void *));
/* tokenizer_utils.c */
int		set_type(int status, char *str, int i);
int		is_sep(char *str, int i);
int		set_word(t_token **token, char *str, int i, int start);
int		set_sep(t_token **tokens, char *str, int i, int type);
int		set_word_sep(int *i, char *str, int start, t_data *data);
/* cmds_utils.c */
void	free_cmd(t_cmd *cmd, void (*del)(void *));
void	free_cmdlst(t_cmd **cmds, void (*del)(void *));
/* signals.c */
void	reset_signal(int signal_nb);
void	skip_sigquit(void);
void	signals_on(void);
/* parser.c */
bool	parser(t_data *data);
/* var_check.c */
int		is_var(t_token **tokens);
/* var_grammer.c */
int		check_consecutives(t_token **tokens);
/* var_expander.c */
int		var_expander(t_data *data, t_token **tokens);
char	*var_expander_hdc(t_data *data, char *str);
/* var_replacer.c */
int		var_replace(t_token **tokens, char *var, int i);
char	*var_replace_hdc(char *str, char *var, int i);
/* var_utils.c */
void	var_copy(char *result, char *var, int *k);
int		var_len(char *str);
char	*var_identifier(char *str);
char	*set_token_str(char *old, char *var, int len, int index);
/* var_restorer.c */
char	*var_restore(t_token *token, char *str, t_data *data);
/* quotes_handler.c */
int		len_count(char *str, int count, int i);
bool	str_quotes(char *str);
int		quote_handler(t_data *data);
/* quotes_cleaner.c */
int		quote_remover(t_token **tokens);
/* cmds_init.c */
void	init_commands(t_data *data, t_token *token);
/* cmds_lst_utils.c */
t_cmd	*create_cmd(bool value);
void	add_cmd(t_cmd **cmds, t_cmd *new_cmd);
t_cmd	*last_cmd(t_cmd *cmd);
/* filler_echo.c */
int		create_arg_echo(t_token **token, t_cmd *cmd);
int		add_arg_echo(t_token **token, t_cmd *cmd);
/* filler_echo_utils.c */
int		count_args(t_token *tokens);
void	remove_empty_args(t_token **tokens);
char	*var_joiner(t_token **token);
char	**add_args_echo_tab(int len, char **tab, t_cmd *cmd, t_token *tmp);
/* filler_args.c */
int		create_arg_def(t_token **token, t_cmd *cmd);
char	**add_args_def_tab(int len, char **tab, t_cmd *cmd, t_token **token);
int		add_arg_def(t_token **token, t_cmd *cmd);
int		fill_args(t_token **token, t_cmd *cmd);
/* filler_hdc.c */
bool	fill_hdc(t_data *data, t_io_fds *io, int fd);
/* pase_word.c */
void	parse_word(t_cmd **cmd, t_token **tokens);
/* parse_rdout.c */
bool	del_prev_file(t_io_fds *io, bool infile);
void	parse_redirout(t_cmd **cmds, t_token **tokens);
/* parse_rdin.c */
void	parse_redirin(t_cmd **cmds, t_token **tokens);
/* parse_hdc.c */
bool	get_hdc(t_data *data, t_io_fds *io);
void	parse_heredoc(t_data *data, t_cmd **cmds, t_token **tokens);
/* parse_append.c */
void	parse_append(t_cmd **cmds, t_token **tokens);
/* parse_pipe.c */
void	parse_pipe(t_cmd **cmds, t_token **tokens);
/* parse_path.c */
char	*get_cmd_path(t_data *data, char *name);
/* execute.c */
int		execution(t_data *data);
/* exec_cmd.c */
int		exec_builtin(t_data *data, t_cmd *cmd);
int		execute_command(t_data *data, t_cmd *cmd);
/* exec_utils.c */
bool	check_dir_command(char *cmd);
int		check_not_found(t_data *data, t_cmd *cmd);
/* cd.c */
int		builtin_cd(t_data *data, char **args);
/* echo.c */
int		builtin_echo(char **args);
/* pwd.c */
int		builtin_pwd(t_data *data);
/* env.c */
int		builtin_env(t_data *data, char **args);
/* export.c */
int		builtin_export(t_data *data, char **args);
/* unset.c */
int		builtin_unset(t_data *data, char **args);
/* exit.c */
int		builtin_exit(t_data *data, char **args);

#endif
