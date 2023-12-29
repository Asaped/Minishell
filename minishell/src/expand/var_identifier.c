/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_identifier.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:39:43 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:00:51 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Vérifie si un caractère est valide pour une clé de venv.
// Un caractère valide est alphanumérique ou un '_'.
bool	is_valid_char(char c)
{
	if (ft_isalnum(c) == 0 && c != '_')
		return (false);
	else
		return (true);
}

// Calcule la longueur de la clé de venv dans une chaîne.
// Commence après le caractère '$' et s'arrête a char non valid ou '\0'.
// Les caractères valides sont définis par la fonction 'is_valid_char'.
int	venv_len(char *str)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (str[i] != '$')
		i++;
	i++;
	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '?')
		return (count + 1);
	while (str[i])
	{
		if (is_valid_char(str[i]) == false)
			break ;
		count++;
		i++;
	}
	return (count);
}

// Identifie la clé de la variable d'environnement dans une chaîne.
// Utilise 'venv_len' pour déterminer la longueur de la clé.
// Extrait la clé et la concatène avec '=' pour retourner la paire clé=valeur.
char	*var_identifier(char *str)
{
	char	*var;
	char	*tmp;
	int		start;
	int		len;
	int		i;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			start = i + 1;
			break ;
		}
		i++;
	}
	len = venv_len(str);
	var = ft_substr(str, start, len);
	if (!var)
		return (NULL);
	tmp = ft_strjoin(var, "=");
	free_ptr(var);
	var = tmp;
	return (var);
}
