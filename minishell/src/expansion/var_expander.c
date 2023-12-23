/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:22:09 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:06:48 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	update_status(t_token **tokens, char c)
{
	if (c == '\'' && (*tokens)->status == DEF)
		(*tokens)->status = SQ;
	else if (c == '\"' && (*tokens)->status == DEF)
		(*tokens)->status = DQ;
	else if (c == '\'' && (*tokens)->status == SQ)
		(*tokens)->status = DEF;
	else if (c == '\"' && (*tokens)->status == DQ)
		(*tokens)->status = DEF;
}

static bool	is_next_sep(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (true);
	return (false);
}

static bool	quoted_var(char *str, int i)
{
	if (i > 0)
	{
		if (str[i - 1] == '\"' && str[i + 1] == '\"')
			return (true);
	}
	return (false);
}

int	var_expander(t_data *data, t_token **tokens)
{
	t_token	*tmp;
	int		i;

	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			i = 0;
			while (tmp->str[i])
			{
				update_status(&tmp, tmp->str[i]);
				if (tmp->str[i] == '$'
					&& is_next_sep(tmp->str[i + 1]) == false
					&& quoted_var(tmp->str, i) == false
					&& (tmp->status == DEF || tmp->status == DQ))
					var_replace(&tmp, var_restore(tmp, tmp->str + i, data), i);
				else
					i++;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*var_expander_hdc(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && is_next_sep(str[i + 1]) == false
			&& quoted_var(str, i) == false)
			str = var_replace_hdc(str, var_restore(NULL, str + i, data), i);
		else
			i++;
	}
	return (str);
}
