/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:42:33 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:06:45 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Copie la valeur d'une variable d'environnement dans une nouvelle chaîne.
// Utilisée lors du remplacement d'une référence de variable par sa valeur.
// `pos` est mis à jour pour refléter la nouvelle position dans la chaîne.
static void	venv_copy_val(char *new_str, char *venv_val, int *pos)
{
	int	k;

	k = 0;
	while (venv_val[k])
	{
		new_str[*pos] = venv_val[k];
		k++;
		(*pos)++;
	}
}

// Crée une nouvelle chaîne de token avec la venv remplacée par sa valeur
// Utilise `venv_copy_val` pour copier la valeur de la variable dans une new str
// Utilisée pour mettre à jour les tokens avec les valeurs de venv
char	*get_new_token_string(char *old, char *var_val, int new_len, int index)
{
	int		i;
	int		k;
	char	*new_str;

	i = 0;
	k = 0;
	new_str = malloc(sizeof(char) * new_len);
	if (!new_str)
		return (NULL);
	while (old[i])
	{
		if (old[i] == '$' && i == index)
		{
			venv_copy_val(new_str, var_val, &k);
			i = i + venv_len(old + index) + 1;
			if (old[i] == '\0')
				break ;
		}
		new_str[k++] = old[i++];
	}
	new_str[k] = '\0';
	return (new_str);
}
