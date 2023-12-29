/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_replacer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:41:49 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:04:24 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Supprime la référence de venv d'une chaîne.
// Crée une nouvelle str sans la référence de variable et remplace l'ancienne
// Utilisée quand une venv est non définie ou sa valeur est NULL
static int	venv_clear(t_token **token_node, char *str, int index)
{
	int		i;
	int		k;
	int		len;
	char	*new_str;

	i = 0;
	k = 0;
	len = ft_strlen(str) - venv_len(str + index);
	new_str = (char *)malloc(sizeof(char) * len + 1);
	if (!new_str)
		return (1);
	while (str[i])
	{
		if (str[i] == '$' && i == index)
		{
			i = i + venv_len(str + index) + 1;
			if (str[i] == '\0')
				break ;
		}
		new_str[k++] = str[i++];
	}
	new_str[k] = '\0';
	free_ptr((*token_node)->str);
	(*token_node)->str = new_str;
	return (0);
}

// Remplace la référence de variable dans une chaîne par sa valeur.
// Calcule la taille de la nouvelle chaîne et crée une chaîne a jour.
static char	*erase_replace(t_token **tokens, char *str, char *var_value, int i)
{
	char	*newstr;
	int		newstr_size;

	newstr_size = (ft_strlen(str) - venv_len(str + i)
			+ ft_strlen(var_value));
	newstr = get_new_token_string(str, var_value, newstr_size, i);
	if (tokens && *tokens)
	{
		free_ptr((*tokens)->str);
		(*tokens)->str = newstr;
	}
	return (newstr);
}

// Remplace la référence de variable dans un token par sa valeur
// Utilise `venv_clear` si la valeur de la variable est NULL
// Utilise `erase_replace` pour remplacer la réf de variable par sa valeur
int	var_replacer(t_token **token_node, char *var_value, int index)
{
	if (var_value == NULL)
	{
		if (venv_clear(token_node, (*token_node)->str, index) == FAILURE)
		{
			free_ptr(var_value);
			return (FAILURE);
		}
	}
	else
	{
		if (!erase_replace(token_node, (*token_node)->str, var_value, index))
		{
			free_ptr(var_value);
			return (FAILURE);
		}
	}
	free_ptr(var_value);
	return (SUCCESS);
}

// Remplace la référence de variable dans une chaîne (spécifique à heredoc)
// Utilise `erase_replace` pour effectuer le remplacement
char	*replace_str_heredoc(char *str, char *var_value, int index)
{
	char	*tmp;

	tmp = NULL;
	if (var_value == NULL)
		*str = '\0';
	else
	{
		tmp = str;
		str = erase_replace(NULL, str, var_value, index);
		free_ptr(tmp);
	}
	free_ptr(var_value);
	return (str);
}
