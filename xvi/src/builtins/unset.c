/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:41:21 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:42:22 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_unset(t_data *data, char **args)
{
	int	pos;
	int	i;
	int	result;

	result = EXIT_SUCCESS;
	i = 1;
	while (args[i])
	{
		if (!valid_venv_key(args[i]) || ft_strchr(args[i], '='))
		{
			errmsg_cmd("unset", args[i], "not valid identifier", false);
			result = EXIT_FAILURE;
		}
		else
		{
			pos = venv_index(data->env, args[i]);
			if (pos != -1)
				venv_remover(data, pos);
		}
		i++;
	}
	return (result);
}
