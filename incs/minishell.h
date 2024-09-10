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

# define WHITESPACE " \t\n\r\f\v"
# define FALSE 0
# define TRUE 1
# define t_bool int

typedef enum e_type
{
	BUILTIN,
	CMD,
	STRING,
	OPERATOR,
	$,
	UNKNOWN
}				t_type;

typedef struct	s_token
{
	t_type	type;
	int		len;
	char	*value;
	char	*path_bin;
}				t_token;

typedef struct	s_mini
{
	char	*input;
	t_token	*token;
	int		tlen;
	char	**env;
	char	path[4096];
}				t_mini;

// env.c
char    *get_env_value(t_mini *shell, char *str);

// init.c
t_bool		init_shell(t_mini *shell);

// token_utils.c
int		wordlen(const char *s, int i);

char	*worddup(const char *s, int i, int *n);

int		skip_quote(const char *str, int i);

// token.c
t_bool	tokenize(t_mini *shell);

// free.c
t_bool	ft_error(char *error);

void	free_tab(char **tab);

void	free_token(t_token *token, int tlen);

t_bool	ft_free(t_mini *shell, char *error, int flag);

// signal.c
void	signal_handler(void);

#endif