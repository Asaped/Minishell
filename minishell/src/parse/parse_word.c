/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 13:02:12 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/24 15:08:47 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	contains_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (true);
		i++;
	}
	return (false);
}

static void	split_var_cmd_token(t_cmd *last_cmd, char *cmd_str)
{
	t_token		*new_tokens;
	t_token		*tmp;
	char		**strs;
	int			i;

	new_tokens = NULL;
	strs = ft_split(cmd_str, ' ');
	if (!strs)
		return ;
	last_cmd->command = ft_strdup(strs[0]);
	if (strs[1])
		new_tokens = create_token(ft_strdup(strs[1]), NULL, WORD, DEFAULT);
	tmp = new_tokens;
	i = 1;
	while (strs[++i])
		add_token(&new_tokens,
			create_token(ft_strdup(strs[i]), NULL, WORD, DEFAULT));
	add_token(&new_tokens,
		create_token(NULL, NULL, END, DEFAULT));
	fill_args(&new_tokens, last_cmd);
	clear_tokens(&tmp, &free_ptr);
	free_tab(strs);
}

void	parse_word(t_cmd **cmd, t_token **token_lst)
{
	t_token	*temp;
	t_cmd	*last;

	temp = *token_lst;
	while (temp->type == WORD || temp->type == VAR)
	{
		last = last_cmd(*cmd);
		if (temp->prev == NULL || (temp->prev && temp->prev->type == PIPE)
			|| last->command == NULL)
		{
			if (temp->type == VAR && contains_space(temp->str))
				split_var_cmd_token(last, temp->str);
			else
				last->command = ft_strdup(temp->str);
			temp = temp->next;
		}
		else
			fill_args(&temp, last);
	}
	*token_lst = temp;
}
