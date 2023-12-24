/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:43:01 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/24 13:41:42 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	update_status(t_token **token_node, char c)
{
	if (c == '\'' && (*token_node)->status == DEFAULT)
		(*token_node)->status = SQ;
	else if (c == '\"' && (*token_node)->status == DEFAULT)
		(*token_node)->status = DQ;
	else if (c == '\'' && (*token_node)->status == SQ)
		(*token_node)->status = DEFAULT;
	else if (c == '\"' && (*token_node)->status == DQ)
		(*token_node)->status = DEFAULT;
}

static bool	is_next_char_a_sep(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (true);
	else
		return (false);
}

static bool	var_between_quotes(char *str, int i)
{
	if (i > 0)
	{
		if (str[i - 1] == '\"' && str[i + 1] == '\"')
			return (true);
		else
			return (false);
	}
	return (false);
}

int	var_expander(t_data *data, t_token **token_lst)
{
	t_token	*temp;
	int		i;

	temp = *token_lst;
	while (temp)
	{
		if (temp->type == VAR)
		{
			i = 0;
			while (temp->str[i])
			{
				update_status(&temp, temp->str[i]);
				if (temp->str[i] == '$'
					&& is_next_char_a_sep(temp->str[i + 1]) == false
					&& var_between_quotes(temp->str, i) == false
					&& (temp->status == DEFAULT || temp->status == DQ))
					var_replacer(&temp,
						var_recover(temp, temp->str + i, data), i);
				else
					i++;
			}
		}
		temp = temp->next;
	}
	return (0);
}

char	*var_expand_hdc(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$'
			&& is_next_char_a_sep(str[i + 1]) == false
			&& var_between_quotes(str, i) == false)
			str = replace_str_heredoc(str, var_recover(NULL, str + i, data), i);
		else
			i++;
	}
	return (str);
}
