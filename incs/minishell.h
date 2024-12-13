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

void	init_fds(t_cmd *cmd);

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
void	signal_handler_interactive(void);

void    signal_handler_non_interactive(void);

// debug.c
void	print_token(t_mini *shell);

void	print_cmd(t_mini *shell);

// simple_command.c
void simple_command_exec(t_mini *shell);
void simple_command_child(t_mini *shell);

//main_exec.c
void    main_exec(t_mini *shell);
void    execute_first_command(t_mini *shell);
void    execute_middle_command(t_mini *shell, int index);
void    execute_last_command(t_mini *shell, int index);
void    check_fd(int fd, const char* fd_name);
//main_exe2.c
void    main_exe2(t_mini *shell);
void    child_process(t_mini *shell, int index, int *pipefd);
//void    main_exe3(t_mini *shell);
//main_exec3.c
int	        execute_command(t_mini *shell, int index);
int	        execute(t_mini *shell);
void	    close_fds(t_mini *shell, bool close_backups, int index);
//redirect.c
bool	    check_infile_outfile(t_mini_fd *fds);
void	    close_pipe_fds(t_mini *shell, t_cmd *skip_cmd);
bool	    set_pipe_fds(t_mini *shell, t_cmd *cmd, int index);
bool	    create_pipes(t_mini *shell);
bool	    redirect_io(t_cmd *cmd);
int         restore_io(t_cmd *cmd);
//static int	init_exec(t_mini *shell);
//static int	get_children(t_mini *data);
//static int	create_children(t_mini *shell);

#endif