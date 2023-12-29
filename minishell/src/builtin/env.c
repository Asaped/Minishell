/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:27:05 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 10:55:16 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// affiche les variable d'environnement du shell sur la sortie standards
int	builtin_env(t_data *data, char **args)
{
	int	i;

	if (args && args[1])
		return (errmsg_cmd("env", NULL, "too many arguments", ERROR));
	i = 0;
	if (!data->env)
		return (EXIT_FAILURE);
	while (data->env[i])
		ft_putendl_fd(data->env[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
