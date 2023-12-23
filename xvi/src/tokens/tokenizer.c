/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:17:56 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:04:20 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	tokenizer(t_data *data, char *input)
{
	t_tools	tools;
	int		i;

	i = -1;
	tools.start = 0;
	tools.end = ft_strlen(input);
	tools.type = DEF;
	while (++i <= tools.end)
	{
		tools.type = set_type(tools.type, input, i);
		if (tools.type == DEF)
			tools.start = set_word_sep(&i, input, tools.start, data);
	}
	if (tools.type != DEF)
	{
		if (tools.type == DQ)
			errmsg("unexpected EOF while looking for matching", "\"", true);
		else if (tools.type == SQ)
			errmsg("unexpected EOF while looking for matching", "\'", true);
		errmsg("error syntax", "unexpected EOF", false);
		return (1);
	}
	return (0);
}
