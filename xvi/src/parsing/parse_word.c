/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 09:59:41 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 20:04:29 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	has_spaces(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			return (true);
	}
	return (false);
}

static void	clean_var_tok_cmd(t_cmd *last, char *cmd)
{
	t_token	*result;
	t_token	*tmp;
	char	**tab;
	int		i;

	result = NULL;
	tab = ft_split(cmd, ' ');
	if (!tab)
		return ;
	last->command = ft_strdup(tab[0]);
	if (tab[1])
		result = create_token(ft_strdup(tab[1]), NULL, WORD, DEF);
	tmp = result;
	i = 1;
	while (tab[++i])
		add_token(&result, create_token(ft_strdup(tab[i]), NULL, WORD, DEF));
	add_token(&result, create_token(NULL, NULL, END, DEF));
	fill_args(&result, last);
	free_tokenlst(&tmp, &free_ptr);
	free_tab(tab);
}

void	parse_word(t_cmd **cmd, t_token **tokens)
{
	t_token	*tmp_tok;
	t_cmd	*tmp_cmd;

	tmp_tok = *tokens;
	while (tmp_tok->type == WORD || tmp_tok->type == VAR)
	{
		tmp_cmd = last_cmd(*cmd);
		if (!tmp_tok->prev || !tmp_cmd->command
			|| (tmp_tok->prev && tmp_tok->prev->type == PIPE))
		{
			if (tmp_tok->type == VAR && has_spaces(tmp_tok->str))
				clean_var_tok_cmd(tmp_cmd, tmp_tok->str);
			else
				tmp_cmd->command = ft_strdup(tmp_tok->str);
			tmp_tok = tmp_tok->next;
		}
		else
			fill_args(&tmp_tok, tmp_cmd);
	}
	*tokens = tmp_tok;
}
