/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   venv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:06:51 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/16 18:08:36 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*
	Toutes les variables d'environnements sont stockées dans **environ
	Ces fonction recupere toutes les variables d'environnements et les stocke
	dans une liste chainée (t_venv) bidirectionnelle.
	La liste entiere sera stockée dans la structure t_data
*/

extern char	**environ;


static void	add_venv(t_venv **head, char *name, char *value)
{
	t_venv	*new_env;

	new_env = (t_venv *)malloc(sizeof(t_venv));
	if (!new_env)
	{
		free_env(*head);
		error_exit("Allocation mémoire échouée new_env");
	}
	new_env->name = ft_strdup(name);
	new_env->value = ft_strdup(value);
	if (!new_env->name || !new_env->value)
	{
		free_env(*head);
		error_exit("Allocation mémoire échouée new_env value/name");
	}
	new_env->next = *head;
	*head = new_env;
}

void	init_venv(t_venv **env_list)
{
	char	**split_result;
	char	**tab_env;

	tab_env = environ;
	while (*tab_env != NULL)
	{
		split_result = ft_split(*tab_env, '=');
		if (split_result != NULL && split_result[0] != NULL)
		{
			if (split_result[1] == NULL)
				split_result[1] = ft_strdup("");
			add_venv(env_list, split_result[0], split_result[1]);
		}
		free_tab(split_result);
		tab_env++;
	}
}
