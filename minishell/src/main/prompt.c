/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:29:29 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/26 09:15:52 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_size(char *user, char *lvl, char *path)
{
	int	size_strs;
	int	size_colors;

	size_strs = ft_strlen(user) + ft_strlen(lvl) + ft_strlen(path);
	size_colors = (ft_strlen(R) * 3) + (ft_strlen(RST) * 3);
	return (size_strs + size_colors);
}

static char	*get_prompt_result(char *user, char *lvl, char *path)
{
	char	*result;

	result = malloc(sizeof(char) * get_size(user, lvl, path) + 7 + 1);
	if (!result)
		result = ft_strdup(Y "[Minishell] $> " RST);
	else
	{
		result = ft_strcat(result, "[" R);
		result = ft_strcat(result, user);
		result = ft_strcat(result, RST "] (" M);
		result = ft_strcat(result, lvl);
		result = ft_strcat(result, RST ") " B);
		result = ft_strcat(result, path);
		result = ft_strcat(result, RST);
		result[get_size(user, lvl, path) + 7] = '\0';
	}
	return (result);
}

char	*get_prompt(t_data *data)
{
	char	*user;
	char	*lvl;
	char	*path;

	user = venv_value(data->env, "USER");
	if (!user)
		user = "Minishell";
	lvl = venv_value(data->env, "SHLVL");
	if (!lvl)
		lvl = "42";
	path = venv_value(data->env, "PWD");
	if (!path)
		path = "I/dont/know/where/I/am/";
	return (get_prompt_result(user, lvl, path));
}
