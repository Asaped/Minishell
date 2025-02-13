/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:06:54 by nigateau          #+#    #+#             */
/*   Updated: 2025/01/20 21:06:54 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef int	t_bool;

/* ERROR CODES */
# define ERROR 				-1
# define SUCCESS 			0
# define TRUE				1
# define FALSE				0
# define IS_DIRECTORY 		126
# define UNKNOWN_COMMAND 	127

extern int	g_exit_status;

typedef enum e_type
{
	BUILTIN,
	CMD,
	STRING,
	OPERATOR,
	UNKNOWN
}				t_type;

typedef struct s_token
{
	t_type	type;
	int		len;
	char	*value;
	char	*path_bin;
}				t_token;

typedef struct s_cmd
{
	char			**token;
	char			*path_bin;
	int				tlen;
	char			*heredoc_key;
	char			*input;
	char			*output;
	int				fd_in;
	int				fd_out;
	int				fd_pipe[2];
	int				*pipe_fd;
}				t_cmd;

typedef struct s_mini
{
	t_cmd	*cmd;
	t_token	*token;
	int		clen;
	int		tlen;
	pid_t	pid;
	char	*input;
	char	**env;
	char	*path;
}				t_mini;

#endif