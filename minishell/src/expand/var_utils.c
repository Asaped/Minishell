/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:42:33 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/24 13:42:13 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	var_copy_val(char *new_str, char *var_value, int *j)
{
	int	k;

	k = 0;
	while (var_value[k])
	{
		new_str[*j] = var_value[k];
		k++;
		(*j)++;
	}
}

char	*get_new_token_string(char *old, char *var_val, int new_len, int index)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * new_len);
	if (!new_str)
		return (NULL);
	while (old[i])
	{
		if (old[i] == '$' && i == index)
		{
			var_copy_val(new_str, var_val, &j);
			i = i + var_len(old + index) + 1;
			if (old[i] == '\0')
				break ;
		}
		new_str[j++] = old[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}
