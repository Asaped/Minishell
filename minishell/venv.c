/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   venv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:06:51 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/14 19:23:42 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

static void	add_venv(t_venv **head, char *name, char *value)
{
	t_venv	*new_env;

	new_env = (t_venv *)malloc(sizeof(t_venv));
	if (!new_env)
		error_exit("Allocation mémoire échouée");
	new_env->name = ft_strdup(name);
	new_env->value = ft_strdup(value);
	new_env->next = *head;
	*head = new_env;
}

void	init_venv(void)
{
	t_venv	*env_list;
	char	**split_result;

	env_list = NULL;
	while (*environ != NULL)
	{
		split_result = ft_split(*environ, '=');
		if (split_result != NULL && split_result[0] != NULL
			&& split_result[1] != NULL)
			add_venv(&env_list, split_result[0], split_result[1]);
		free_tab(split_result);
		environ++;
	}
}
