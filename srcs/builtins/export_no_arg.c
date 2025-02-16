/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.lausanne>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:52:43 by nigateau          #+#    #+#             */
/*   Updated: 2025/02/16 16:21:56 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int count_env(char **env)
{
    int count;

	count = 0;
    while (env[count])
        count++;
    return count;
}

char **copy_env(char **env, int count)
{
    int i = 0;
    char **sorted_env = malloc((count + 1) * sizeof(char *));
    if (!sorted_env)
        return NULL;
    while (i < count)
	{
        sorted_env[i] = env[i];
        i++;
    }
    sorted_env[count] = NULL;
    return (sorted_env);
}

void bubble_sort_env(char **env, int count)
{
    int i = -1;
    int j = -1;
    char *temp;

    while (++i < count)
	{
        j = -1;
        while (++j < count - i - 1)
		{
            if (strcmp(env[j], env[j + 1]) > 0)
			{
                temp = env[j];
                env[j] = env[j + 1];
                env[j + 1] = temp;
            }
        }
    }
}

void print_env_var(char *var)
{
    char *equal_sign;

	if(!var)
		return;
	equal_sign = strchr(var, '=');
    if (equal_sign)
        printf("export %.*s=\"%s\"\n", (int)(equal_sign - var), var, equal_sign + 1);
    else
        printf("export %s\n", var);
}

void print_sorted_env(char **env)
{
	int i;
    int count;
    char **sorted_env;

	i = -1;
	count = count_env(env);
	sorted_env = copy_env(env, count);
    if (!sorted_env)
        return;

    bubble_sort_env(sorted_env, count);

    while (++i < count)
        print_env_var(sorted_env[i]);

    free_tab(sorted_env);
}
