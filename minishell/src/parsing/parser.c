/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:59:23 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 20:07:05 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	is_only_spaces(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] != ' ' || input[i] != '\t')
			return (false);
	}
	return (true);
}

bool	parser(t_data *data)
{
	if (!data->user_input)
		return (false);
	else if (ft_strcmp(data->user_input, "\0") == SUCCESS)
		return (false);
	else if (is_only_spaces(data->user_input))
		return (true);
	add_history(data->user_input);
	if (tokenizer(data, data->user_input) == FAILURE)
		return (false);
	if (data->token->type == END)
		return (false);
	if (is_var(&data->token) == FAILURE)
		return (false);
	var_expander(data, &data->token);
	quote_handler(data);
	init_commands(data, data->token);
	return (true);
}
