/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:18:38 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:45:07 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*safe_join(char *str, char *add)
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

static bool	add_quotes(char *cmd)
{
	if (ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0)
		return (true);
	return (false);
}

int	errmsg_cmd(char *cmd, char *detail, char *err_msg, int err_nb)
{
	char	*msg;
	bool	put_quotes;

	put_quotes = add_quotes(cmd);
	msg = ft_strdup("minishell: ");
	if (cmd)
	{
		msg = safe_join(msg, cmd);
		msg = safe_join(msg, ": ");
	}
	if (detail)
	{
		if (put_quotes)
			msg = safe_join(msg, "'");
		msg = safe_join(msg, detail);
		if (put_quotes)
			msg = safe_join(msg, "'");
		msg = safe_join(msg, ": ");
	}
	msg = safe_join(msg, err_msg);
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
	return (err_nb);
}

void	errmsg(char *err_msg, char *detail, int quotes)
{
	char	*result;

	result = ft_strdup("minishell: ");
	result = safe_join(result, err_msg);
	if (quotes)
		result = safe_join(result, " '");
	else
		result = safe_join(result, ": ");
	result = safe_join(result, detail);
	if (quotes)
		result = safe_join(result, "'");
	ft_putendl_fd(result, STDERR_FILENO);
	free_ptr(result);
}
