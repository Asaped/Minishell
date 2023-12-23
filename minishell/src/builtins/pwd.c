/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:19:42 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:07:46 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_pwd(t_data *data)
{
	char	buffer[PATH_MAX];
	char	*cwd;

	if (data->wdir)
	{
		ft_putendl_fd(data->wdir, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	cwd = getcwd(buffer, PATH_MAX);
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	errmsg_cmd("pwd", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}
