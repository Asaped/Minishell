/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:33:52 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/27 14:14:00 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*strs_joiner(char *str, char *add)
{
	char	*tmp;

	if (!add)
		return (str);
	if (!str)
		return (ft_strdup(add));
	tmp = str;
	str = ft_strjoin(tmp, add);
	free_ptr(tmp);
	return (str);
}

static bool	add_detail_quotes(char *cmd)
{
	if (ft_strncmp(cmd, "export", 7) == SUCCESS
		|| ft_strncmp(cmd, "unset", 6) == SUCCESS)
		return (true);
	return (false);
}

int	errmsg_cmd(char *cmd, char *detail, char *err_msg, int err_nb)
{
	char	*msg;
	bool	detail_quotes;

	detail_quotes = add_detail_quotes(cmd);
	msg = ft_strdup("minishell: ");
	if (cmd != NULL)
	{
		msg = strs_joiner(msg, cmd);
		msg = strs_joiner(msg, ": ");
	}
	if (detail != NULL)
	{
		if (detail_quotes)
			msg = strs_joiner(msg, "`");
		msg = strs_joiner(msg, detail);
		if (detail_quotes)
			msg = strs_joiner(msg, "'");
		msg = strs_joiner(msg, ": ");
	}
	msg = strs_joiner(msg, err_msg);
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
	return (err_nb);
}

void	errmsg(char *errmsg, char *detail, int quotes)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	msg = strs_joiner(msg, errmsg);
	if (quotes)
		msg = strs_joiner(msg, " `");
	else
		msg = strs_joiner(msg, ": ");
	msg = strs_joiner(msg, detail);
	if (quotes)
		msg = strs_joiner(msg, "'");
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
}
