/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:47:38 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/26 09:11:40 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	tokenization(t_data *data, char *str)
{
	int	i;
	int	end;
	int	start;
	int	status;

	i = -1;
	start = 0;
	end = ft_strlen(str);
	status = DEFAULT;
	while (++i <= end)
	{
		status = set_status(status, str, i);
		if (status == DEFAULT)
			start = save_word_or_sep(&i, str, start, data);
	}
	if (status != DEFAULT)
	{
		if (status == DQ)
			errmsg("unexpected EOF while looking for matching", "\"", true);
		else if (status == SQ)
			errmsg("unexpected EOF while looking for matching", "\'", true);
		errmsg("syntax error", "unexpected end of file", false);
		return (FAILURE);
	}
	return (SUCCESS);
}
