/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:07:08 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/16 19:15:20 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <termios.h>
# include <curses.h>
# include <dirent.h>
# include <sys/stat.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <stdbool.h>

# define RST	"\033[0m"
# define R		"\033[31m"
# define G		"\033[32m"
# define Y		"\033[33m"
# define B		"\033[34m"
# define M		"\033[35m"
# define C		"\033[36m"
# define W		"\033[37m"

typedef enum e_type_token
{
	WORD,//				tout
	SPACE,
	PIPE,//				|
	ASSIGN,//			=
	REDIR_IN,//			<
	REDIR_OUT,//		>
	REDIR_APD,//		>>
	REDIR_HDC,//		<<
}	t_type_token;

typedef struct s_token
{
	t_type_token	type;
	char			*value;
	int				len;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_tools
{
	char	*input;
	bool	in_quote;
	int		len;
}			t_tools;

typedef struct s_venv
{
	char			*name;
	char			*value;
	struct s_venv	*next;
	struct s_venv	*prev;
}				t_venv;

typedef struct s_data
{
	char		*user;
	char		*curr_path;
	char		*input;
	char		*prompt_msg;
	t_venv		*venv;
	t_token		*tokens;
}				t_data;

/* Fonctions d'erreurs */
void	error_exit(const char *err_msg);
void	error_back(const char *err_msg);
/* Fonctions de free */
void	free_env(t_venv *head);
void	free_tab(char **tab);
void	free_data(t_data *data);
void	free_tokens(t_token *head);
/* Fonctions d'initialisation */
void	init_data(t_data *data);
void	init_venv(t_venv **env_list);
void	init_prompt(t_data *data);
/* Fonctions de safers */
void	*safe_malloc(size_t bytes);
/* Fonctions orchestrales */
void	processing(t_data *data);
/* Tokenization */
int		init_tokens(t_data *data);
/* Formatting utils */
int		formats_and_checks(t_data *data);
/* Token utils */
void	add_token(t_token **tokens, t_token *new_token);
t_token	*create_token(t_type_token type, char *value, int len);
void	init_token_tools(t_tools *tools, t_data *data);
/* Parse extractor */
void	extract_in_quotes(char **input, char limit, t_token **tok);
void	extract_s_redir(char **input, char redir, t_token **tok);
void	extract_d_redir(char **input, char redir, t_token **tok);
void	extract_operator(char **input, char oper, t_token **tok);
void	extract_words(char **input, t_token **tok);

#endif
