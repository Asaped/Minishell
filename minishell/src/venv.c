/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   venv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:06:51 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/15 16:39:53 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern char	**environ;

static void	increment_ascii(char *nbr_str)
{
	int		length;
	int		i;
	char	current_c;
	int		carry;

	length = ft_strlen(nbr_str);
	carry = 1;
	i = length;
	while (--i >= 0)
	{
		current_c = nbr_str[i];
		if (current_c >= '0' && current_c <= '9')
		{
			if (carry)
			{
				if (current_c == '9')
					nbr_str[i] = '0';
				else
				{
					nbr_str[i] = current_c + 1;
					carry = 0;
				}
			}
		}
	}
}

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
	if (ft_strcmp(new_env->name, "SHLVL") == 0)
		increment_ascii(new_env->value);
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
