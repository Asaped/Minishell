/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:29:02 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 11:55:54 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Sépare les venv "clé=valeur" en deux str distinctes : clé et valeur.
// Utilise un index pour trouver la position du caractère '='.
// Cree un tableau de 2 str contenant la cle et la valeur, la 3eme est NULL
static char	**get_key_value_pair(char *arg)
{
	char	**tmp;
	char	*assign_position;

	assign_position = ft_strchr(arg, '=');
	tmp = malloc(sizeof * tmp * (2 + 1));
	tmp[0] = ft_substr(arg, 0, assign_position - arg);
	tmp[1] = ft_substr(assign_position, 1, ft_strlen(assign_position));
	tmp[2] = NULL;
	return (tmp);
}

// Ajoute ou modifie les variables d'environnement
// Pour chaque argument, extrait la paire clé-valeur
// Vérifie si la clé est valide (caractères alphanumériques et tirets bas)
// Modifie la venv si deja existante, sinon, crée une nouvelle variable
// Affiche toutes les variables d'environnement en cas d'appel sans arguments
int	builtin_export(t_data *data, char **args)
{
	char	**tmp;
	int		i;
	int		ret;

	ret = EXIT_SUCCESS;
	i = 1;
	if (!args[i])
		return (builtin_env(data, NULL));
	while (args[i])
	{
		if (!venv_valid_key(args[i]))
		{
			errmsg_cmd("export", args[i], "not a valid identifier", false);
			ret = EXIT_FAILURE;
		}
		else if (ft_strchr(args[i], '=') != NULL)
		{
			tmp = get_key_value_pair(args[i]);
			venv_set(data, tmp[0], tmp[1]);
			free_tab(tmp);
		}
		i++;
	}
	return (ret);
}
