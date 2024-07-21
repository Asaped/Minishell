#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"

typedef enum e_type
{
	CMD,
	DIR,
	STRING,
	OPTIONN,
	OPERATOR,
	UNKNOWN
}				t_type;

typedef struct	s_token
{
	t_type	type;
	int		pos;
	char	*value;
}				t_token;

typedef struct	s_mini
{
	char	*input;
	t_token	*token;
	int		tlen;
}				t_mini;

// init.c
int		init_shell(t_mini *shell, char *input);

// token_utils.c
int		wordlen(const char *s, int i);

char	*worddup(const char *s, int i, int n);

int		skip_quote(const char *str, int i);

// token.c
void	tokenize(t_mini *shell);

#endif