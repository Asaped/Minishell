/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:00:53 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:07:50 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**venv_set_pair(char *arg)
{
	char	**result;
	char	*assign_position;

	assign_position = ft_strchr(arg, '=');
	result = malloc(sizeof * result * 3);
	if (!result)
		return (NULL);
	result[0] = ft_substr(arg, 0, assign_position - arg);
	result[1] = ft_substr(assign_position, 1, ft_strlen(assign_position));
	result[2] = NULL;
	return (result);
}

int	builtin_export(t_data *data, char **args)
{
	char	**tmp;
	int		i;
	int		result;

	result = EXIT_SUCCESS;
	i = 1;
	if (!args[i])
		return (builtin_env(data, NULL));
	while (args[i])
	{
		if (!valid_venv_key(args[i]))
		{
			errmsg_cmd("export", args[i], "not valid identifier", false);
			result = EXIT_FAILURE;
		}
		else if (ft_strchr(args[i], '=') != NULL)
		{
			tmp = venv_set_pair(args[i]);
			venv_set(data, tmp[0], tmp[1]);
			free_tab(tmp);
		}
		i++;
	}
	return (result);
}
