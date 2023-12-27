/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:30:46 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/27 14:10:22 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_unset(t_data *data, char **args)
{
	int	i;
	int	position;
	int	result;

	result = EXIT_SUCCESS;
	i = 1;
	while (args[i])
	{
		if (!venv_valid_key(args[i]) || ft_strchr(args[i], '=') != NULL)
		{
			errmsg_cmd("unset", args[i], "not a valid identifier", false);
			result = EXIT_FAILURE;
		}
		else
		{
			position = venv_index(data->env, args[i]);
			if (position != -1)
				venv_delete(data, position);
		}
		i++;
	}
	return (result);
}
