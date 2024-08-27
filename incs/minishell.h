#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <signal.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include "readline/history.h"
# include "readline/readline.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define FALSE 0
# define TRUE 1
# define t_bool int

typedef enum e_type
{
	BUILTIN,
	CMD,
	DIR,
	STRING,
	OPTIONN,
	OPERATOR,
	$,
	UNKNOWN
}				t_type;

typedef struct	s_token
{
	t_type	type;
	int		pos;
	int		original_len;
	char	*value;
}				t_token;

typedef struct	s_mini
{
	char	*input;
	t_token	*token;
	int		tlen;
	char	**env;
	char	path[4096];
}				t_mini;

// init.c
t_bool		init_shell(t_mini *shell);

// token_utils.c
int		wordlen(const char *s, int i);

char	*worddup(const char *s, int i, int n);

int		skip_quote(const char *str, int i);

// token.c
void	tokenize(t_mini *shell);

// error.c
int		ft_error(int error);

#endif