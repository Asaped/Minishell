/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:33:52 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 12:36:31 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// ft_strjoin dopé
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

// Verifie si l'ajout de quotes est necessaire (si cmd est export ou unset)
static bool	add_detail_quotes(char *cmd)
{
	if (ft_strncmp(cmd, "export", 7) == SUCCESS
		|| ft_strncmp(cmd, "unset", 6) == SUCCESS)
		return (true);
	return (false);
}

// Ecris le message d'erreur similaire a bash avec ajout de message d'erreur
// Retourne le message d'erreur correspondant
int	errmsg_cmd(char *cmd, char *detail, char *err_msg, int err_nb)
{
	char	*msg;
	bool	detail_quotes;

	detail_quotes = add_detail_quotes(cmd);
	msg = ft_strdup("minishell: ");
	if (cmd != NULL)
	{
		msg = safe_join(msg, cmd);
		msg = safe_join(msg, ": ");
	}
	if (detail != NULL)
	{
		if (detail_quotes)
			msg = safe_join(msg, "`");
		msg = safe_join(msg, detail);
		if (detail_quotes)
			msg = safe_join(msg, "'");
		msg = safe_join(msg, ": ");
	}
	msg = safe_join(msg, err_msg);
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
	return (err_nb);
}

// Ecris un message d'erreur non relié une commande (parsing et lexing surout)
void	errmsg(char *errmsg, char *detail, int quotes)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	msg = safe_join(msg, errmsg);
	if (quotes)
		msg = safe_join(msg, " `");
	else
		msg = safe_join(msg, ": ");
	msg = safe_join(msg, detail);
	if (quotes)
		msg = safe_join(msg, "'");
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
}
