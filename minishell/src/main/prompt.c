/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 08:57:26 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/24 10:35:52 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_shlvl(char **env)
{
	char	*result;
	char	*tmp;

	result = ft_strjoin(" (", M);
	tmp = ft_strdup(venv_value(env, "SHLVL"));
	if (!tmp)
		tmp = ft_strdup("1");
	result = ft_strjoin(result, tmp);
	free_ptr(tmp);
	result = ft_strjoin(result, RST);
	result = ft_strjoin(result, ") ");
	return (result);
}

static char	*get_user(char **env)
{
	char	*tmp;
	char	*result;

	result = ft_strjoin("[", R);
	tmp = ft_strdup(venv_value(env, "USER"));
	result = ft_strjoin(result, tmp);
	free_ptr(tmp);
	tmp = ft_strjoin(RST, "] ");
	result = ft_strjoin(result, tmp);
	free_ptr(tmp);
	result = ft_strjoin(result, get_shlvl(env));
	return (result);
}

char	*create_prompt(t_data *data)
{
	char	*result;
	char	*tmp;
	char	buff[PATH_MAX];

	result = get_user(data->env);
	tmp = getcwd(buff, PATH_MAX);
	result = ft_strjoin(result, B);
	result = ft_strjoin(result, tmp);
	result = ft_strjoin(result, RST);
	result = ft_strjoin(result, " \033[1;33m$>\033[0m ");
	return (result);
}
