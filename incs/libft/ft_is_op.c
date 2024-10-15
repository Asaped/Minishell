/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_op.c                                        :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: moturki <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:00:45 by moturki           #+#    #+#             */
/*   Updated: 2023/10/23 11:00:48 by moturki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_op(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

t_bool	is_pipe(t_token token)
{
	if (token.type == OPERATOR && token.value[0] == '|' && !token.value[1])
		return (TRUE);
	return (FALSE);
}

t_bool	is_heredoc(t_token token)
{
	if (token.type == OPERATOR && token.value[0] == '<' && token.value[1] == '<' && !token.value[2])
		return (TRUE);
	return (FALSE);
}