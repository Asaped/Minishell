/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   venv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:06:51 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/14 20:14:07 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		error_exit("Allocation mémoire échouée");
	new_env->name = ft_strdup(name);
	new_env->value = ft_strdup(value);
	if (ft_strcmp(new_env->name, "SHLVL"))
		increment_ascii(new_env->value);
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
