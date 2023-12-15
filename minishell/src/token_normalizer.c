/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_normalizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:13:27 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/15 17:28:02 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_quote_change(char c, bool *in_quote, char *quote_char)
{
	if (c == '\'' || c == '\"')
	{
		if (*in_quote && c != *quote_char)
			return (0);
		*in_quote = !(*in_quote);
		if (*in_quote)
			*quote_char = c;
		else
			*quote_char = '\0';
	}
	return (1);
}

static int	adjust_quotes(const char *input, char *new_input)
{
	bool	in_quote;
	char	quote_char;
	int		i;
	int		j;

	in_quote = false;
	quote_char = '\0';
	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (!is_quote_change(input[i], &in_quote, &quote_char))
			return (0);
		new_input[j++] = input[i++];
	}
	if (in_quote)
		return (0);
	new_input[j] = '\0';
	return (1);
}

int	normalize_quotes(t_data *data)
{
	char	*new_input;

	new_input = (char *)safe_malloc(ft_strlen(data->input) + 1);
	if (new_input == NULL)
		return (0);
	if (!adjust_quotes(data->input, new_input))
	{
		free(new_input);
		return (0);
	}
	free(data->input);
	data->input = new_input;
	return (1);
}
