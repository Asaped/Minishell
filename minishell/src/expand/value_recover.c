/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_recover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:41:22 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 12:51:09 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Verifie si la venv existe
static int	venv_exists(t_data *data, char *var)
{
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(var);
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], var, len) == SUCCESS)
			return (SUCCESS);
	}
	return (FAILURE);
}

// Cherche et retourne une copie de la valeur d'une venv
static char	*venv_search(t_data *data, char *var)
{
	char	*str;
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(var);
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], var, len) == SUCCESS)
			break ;
	}
	str = ft_strdup(data->env[i] + len);
	return (str);
}

// Récupère la valeur d'une variable à partir d'un token
// Identifie la variable dans le token et récupère sa valeur
// Gère le cas spécial de la variable '$?', renvoyant le statut de sortie
char	*var_recover(t_token *token, char *str, t_data *data)
{
	char	*value;
	char	*var;

	var = var_identifier(str);
	if (var && venv_exists(data, var) == SUCCESS)
	{
		if (token != NULL)
			token->var_exists = true;
		value = venv_search(data, var);
	}
	else if (var && var[0] == '?' && var[1] == '=')
		value = ft_itoa(g_exit_status);
	else
		value = NULL;
	free_ptr(var);
	return (value);
}
