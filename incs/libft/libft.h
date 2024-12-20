/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moturki <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:17:59 by moturki           #+#    #+#             */
/*   Updated: 2023/11/17 22:49:48 by moturki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include "../struct.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

int		ft_is_upper_case(char c);

char    *lower_str(char *str);

int		ft_tablen(char **tab);

char	**ft_tabdup(char **src);

int 	is_whitespace(char c);

t_bool	check_pipe(char *str, int len);

int		is_only_whitespace(char *str);

int		skip_quote(const char *str, int i);

int		skip_op(const char *str, int i);

int		is_quote(char c);

int		is_op(char c);

int		is_file(char *str);

int		wordlen(const char *s, int i);

int 	wordlen2(char *str, int *i);

int		pipelen(t_token *token, int tlen);

int		count_word(char *str, int i, int count);

int		get_token_length(t_token *token, int i, int tlen);

t_bool	is_pipe(t_token token);

t_bool	is_heredoc(t_token token);

t_bool	is_unclosed_quote(char *str);

char	*worddup(const char *s, int i, int n);

int		is_builtin(char *str);

int		ft_isalpha(int c);

int		ft_isdigit(int c);

int		ft_isascii(int c);

int		ft_isalnum(int c);

int		ft_isprint(int c);

int		ft_strlen(const char *s);

size_t	ft_strlcpy(char *dst, const char *src, size_t size);

void	*ft_memset(void *s, int c, size_t n);

void	*ft_memmove(void *dest, const void *src, size_t n);

void	*ft_memcpy(void *dest, const void *src, size_t n);

void	ft_bzero(void *s, size_t n);

char	*ft_strrchr(const char *s, int c);

char	*ft_strchr(const char *s, int c);

int		ft_toupper(int c);

int		ft_tolower(int c);

void	*ft_memchr(const void *s, int c, size_t n);

int		ft_memcmp(const void *s1, const void *s2, size_t n);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

size_t	ft_strlcpy(char *dst, const char *src, size_t size);

size_t	ft_strlcat(char *dst, const char *src, size_t size);

char	*ft_strnstr(const char *big, const char *little, size_t len);

int		ft_atoi(const char *nptr);

char	*ft_strdup(const char *s);

char	*ft_strndup(const char *s, int len);

void	*ft_calloc(size_t nmemb, size_t size);

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strjoin(char *s1, char *s2);

char	*ft_strjoin3(char *s1, char *s2);

char	*ft_strjoin4(char *s1, char *s2);

char	*ft_strjoin5(char *s1, char *s2);

char	*ft_strtrim(char const *s1, char const *set);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void	ft_putchar_fd(char c, int fd);

void	ft_putstr_fd(char *s, int fd);

void	ft_putendl_fd(char *s, int fd);

void	ft_putnbr_fd(int n, int fd);

char	**ft_split(char const *s, char c);

char	*ft_itoa(int n);

void	ft_striteri(char *s, void (*f)(unsigned int, char *));

t_list	*ft_lstnew(void *content);

void	ft_lstadd_front(t_list **lst, t_list *new);

int		ft_lstsize(t_list *lst);

t_list	*ft_lstlast(t_list *lst);

void	ft_lstadd_back(t_list **lst, t_list *new);

void	ft_lstdelone(t_list *lst, void (*del)(void *));

void	ft_lstclear(t_list **lst, void (*del)(void *));

void	ft_lstiter(t_list *lst, void (*f)(void *));

#endif
