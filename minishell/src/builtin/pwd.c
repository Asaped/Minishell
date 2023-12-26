/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:30:14 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/26 08:40:44 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_pwd(t_data *data)
{
	char	buf[PATH_MAX];
	char	*cwd;

	if (data->wdir)
	{
		ft_putendl_fd(data->wdir, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	cwd = getcwd(buf, PATH_MAX);
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	errmsg_cmd("pwd", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}
