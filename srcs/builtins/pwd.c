/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:04:24 by nigateau          #+#    #+#             */
/*   Updated: 2025/01/20 21:04:27 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool	ft_pwd(void)
{
	char	path[4096];

	if (getcwd(path, 4096) == NULL)
		return (ft_error(strerror(errno)), ft_error("\n"), TRUE);
	ft_putendl_fd(path, STDOUT_FILENO);
	return (FALSE);
}
