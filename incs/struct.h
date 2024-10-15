#ifndef STRUCT_H
# define STRUCT_H

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
	UNKNOWN
}				t_type;

typedef struct	s_token
{
	t_type	type;
	int		len;
	char	*value;
	char	*path_bin;
}				t_token;

typedef struct	s_cmd
{
	t_token			*token;
	int				tlen;
	char			*heredoc_key;
	char			*input;
	char			*output;
	int				fd_in;
	int				fd_out;
	int				fd_pipe[2];
}				t_cmd;

typedef struct	s_mini
{
	t_cmd	*cmd;
	t_token	*token;
	int		clen;
	int		tlen;
	char	*input;
	char	**env;
	char	path[4096];
}				t_mini;

#endif