/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:39:08 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:54:10 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Recherche le chemin valide pour une commande donnée.
// Vérifie l'access et les droits d'execution
static char	*find_valid_cmd_path(char *cmd, char **paths)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
		{
			errmsg_cmd("malloc", NULL,
				"an unexpected error occured", EXIT_FAILURE);
			return (NULL);
		}
		if (access(cmd_path, F_OK | X_OK) == SUCCESS)
			return (cmd_path);
		free_ptr(cmd_path);
		i++;
	}
	return (NULL);
}

// Récupère et divise les chemins du système stockés dans PATH
// Vérifie si la variable PATH est définie dans l'env
// Divise la chaîne de PATH en utilisant ':' comme séparateur
// Retourne un tableau NULL si PATH n'est pas défini ou si erreur
static char	**get_paths_from_env(t_data *data)
{
	char	**env_paths;

	if (venv_index(data->env, "PATH") == -1)
		return (NULL);
	env_paths = ft_split(venv_value(data->env, "PATH"), ':');
	if (!env_paths)
		return (NULL);
	return (env_paths);
}

// Analyse et trouve le chemin valide pour une commande
// Obtient les chemins d'env et check si la cmde est spécifiée avec un chemin
// Si aucun chemin n'est spécifié, cherche dans les chemins d'env
// Retourne le chemin de la commande si trouvé ou NULL si échec
char	*parse_cmd_path(t_data *data, char *name)
{
	char	**env_paths;
	char	*cmd;
	char	*cmd_path;

	if (!name)
		return (NULL);
	env_paths = get_paths_from_env(data);
	if (!env_paths)
		return (NULL);
	cmd = ft_strjoin("/", name);
	if (!cmd)
	{
		free_tab(env_paths);
		return (NULL);
	}
	cmd_path = find_valid_cmd_path(cmd, env_paths);
	if (!cmd_path)
	{
		free_ptr(cmd);
		free_tab(env_paths);
		return (NULL);
	}
	return (cmd_path);
}
