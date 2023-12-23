/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_restorer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:22:36 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:52:56 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	var_exist(t_data *data, char *var)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(var);
	while (data->env[++i])
		if (ft_strncmp(data->env[i], var, len) == 0)
			return (0);
	return (1);
}

static char	*var_set_value(t_data *data, char *var)
{
	char	*result;
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(var);
	while (data->env[++i])
		if (ft_strncmp(data->env[i], var, len) == 0)
			break ;
	result = ft_strdup(data->env[i] + len);
	return (result);
}

char	*var_restore(t_token *token, char *str, t_data *data)
{
	char	*value;
	char	*var;

	var = var_identifier(str);
	if (var && var_exist(data, var) == 0)
	{
		if (token)
			token->exists = true;
		value = var_set_value(data, var);
	}
	else if (var && var[0] == '?' && var[1] == '=')
		value = ft_itoa(g_exit_status);
	else
		value = NULL;
	free_ptr(var);
	return (value);
}
