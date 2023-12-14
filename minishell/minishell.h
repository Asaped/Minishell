/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:07:08 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/14 19:23:44 by cedmulle         ###   ########.fr       */
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
# include "libft/libft.h"

# define RST	"\033[0m"
# define R		"\033[31m"
# define G		"\033[32m"
# define Y		"\033[33m"
# define B		"\033[34m"
# define M		"\033[35m"
# define C		"\033[36m"
# define W		"\033[37m"

typedef struct	s_venv
{
	char			*name;
	char			*value;
	struct s_venv	*next;
}				t_venv;

/* Fonctions d'erreurs */
void	error_exit(const char *err_message);
/* Fonctions de free */
void	free_lst(t_venv *head);
void	free_tab(char **tab);
/* Fonctions pour variable d'environnement (venv) */
void	init_venv(void);
/* Fonctions de safers */
void	*safe_malloc(size_t bytes);

#endif
