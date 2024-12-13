/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moturki <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:42 by moturki           #+#    #+#             */
/*   Updated: 2023/10/23 11:27:24 by moturki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	wordlen(const char *s, int i)
{
	int	j;

	j = 0;
	if (is_quote(s[i]))
		return (skip_quote(s, i));
	if (is_op(s[i]))
		return (skip_op(s, i));
	while (s[i + j] && !is_whitespace(s[i + j]) && !is_op(s[i + j]) && !is_quote(s[i + j]))
		j++;
	return (j);
}
int	wordlen2(char *str, int *i)
{
    int count;

    count = 0;
    while (str[i[0]])
    {
        if (is_whitespace(str[i[0]]) || str[i[0]] == '$' || is_op(str[i[0]]))
            break;
        count++;
		i[0]++;
    }
    return (count);
}

int	pipelen(t_token *token, int tlen)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < tlen)
		if (token[i].value[0] == '|')
			count++;
	return (count);
}

int	count_word(char *str, int i, int count)
{
	while (str[i])
	{
		while (is_whitespace(str[i]))
			i++;
		if (!str[i])
			break ;
		if (str[i] && !is_whitespace(str[i]) && !is_op(str[i]) && !is_quote(str[i]))
			while (str[i] && !is_whitespace(str[i]) && !is_op(str[i]) && !is_quote(str[i]))
				i++;
		else if (is_quote(str[i]))
			i += skip_quote(str, i);
		else if (is_op(str[i]))
			i += skip_op(str, i);
		count++;
	}
	return (count);
}

int	get_token_length(t_token *token, int i, int tlen)
{
	int	count;
	//int	op;

	count = 0;
	//op = 0;
	while (++i < tlen && !is_pipe(token[i]))
		count++;
	while (--i >= 0 && !is_pipe(token[i]))
	{
		if (token[i].type == OPERATOR && token[i].value[0] != '|')
			count -= 2;
	}
	return (count);
}