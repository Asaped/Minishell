/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:48:25 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/15 17:06:12 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	create_prompt_msg(t_data *data)
{
	char	*tmp;

	tmp = ft_strdup("[");
	tmp = ft_strjoin(tmp, R);
	tmp = ft_strjoin(tmp, data->user);
	tmp = ft_strjoin(tmp, RST);
	tmp = ft_strjoin(tmp, "] ");
	tmp = ft_strjoin(tmp, G);
	tmp = ft_strjoin(tmp, data->curr_path);
	tmp = ft_strjoin(tmp, RST);
	tmp = ft_strjoin(tmp, Y);
	tmp = ft_strjoin(tmp, " $> ");
	tmp = ft_strjoin(tmp, RST);
	data->prompt_msg = ft_strdup(tmp);
	free(tmp);
}

static char	*get_env_value(t_venv *env, const char *name)
{
	t_venv	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	init_prompt(t_data *data)
{
	data->user = get_env_value(data->venv, "USER");
	if (!data->user)
	{
		data->user = ft_strdup("user");
		if (!data->user)
			error_exit("Echec malloc user dans init_data");
	}
	data->curr_path = getcwd(NULL, 0);
	if (!data->curr_path)
		error_exit("Echec malloc curr_path dans init_data.");
	create_prompt_msg(data);
}
