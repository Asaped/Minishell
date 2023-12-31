/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:37:34 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 12:45:07 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Vérifie si le chemin de la commande est un répertoire
// Utilise stat pour obtenir les infos du fichier et vérifie si c'est un dossier
bool	cmd_is_dir(char *cmd)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}

// Vérifie si une commande est introuvable ou non exécutable
// Vérifie la présence de la commande dans le chemin système (PATH)
// Utilise 'access' pour vérifier l'existence et les permissions d'exécution
// Génère des messages d'erreur appropriés en cas d'échec
int	check_cmd_not_found(t_data *data, t_cmd *cmd)
{
	if (ft_strchr(cmd->command, '/') == NULL
		&& venv_index(data->env, "PATH") != -1)
		return (errmsg_cmd(cmd->command, NULL, "command not found",
				CMD_NOT_FOUND));
	if (access(cmd->command, F_OK) != SUCCESS)
		return (errmsg_cmd(cmd->command, NULL, strerror(errno), CMD_NOT_FOUND));
	else if (cmd_is_dir(cmd->command))
		return (errmsg_cmd(cmd->command, NULL, "Is a directory",
				CMD_NOT_EXECUTABLE));
	else if (access(cmd->command, F_OK | X_OK) != SUCCESS)
		return (errmsg_cmd(cmd->command, NULL, strerror(errno),
				CMD_NOT_EXECUTABLE));
	return (EXIT_SUCCESS);
}
