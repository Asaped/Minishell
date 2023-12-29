/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:34:54 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:10:01 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Incrémente le niveau de shell (SHLVL) dans les venv.
// Utilisé pour suivre le nombre de shells imbriqués lancés.
static void	increment_shlvl(t_data *data)
{
	char	*tmp;
	int		swap;

	tmp = venv_value(data->env, "SHLVL");
	if (!tmp)
		tmp = ft_strdup("1");
	swap = ft_atoi(tmp) + 1;
	tmp = ft_itoa(swap);
	venv_set(data, "SHLVL", tmp);
	free(tmp);
	return ;
}

// Initialise l'environnement en copiant les venv du système.
// Duplique chaque variable d'environnement pour une gestion indépendante.
// Incrémente SHLVL pour indiquer un nouveau niveau de shell.
static bool	init_venv(t_data *data, char **env)
{
	int		i;

	data->env = ft_calloc(venv_count(env) + 1, sizeof * data->env);
	if (!data->env)
		return (false);
	i = -1;
	while (env[++i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
			return (false);
	}
	increment_shlvl(data);
	return (true);
}

// Initialise les répertoires de travail actuel et précédent
// Utilise `getcwd` pour obtenir et dupliquer le répertoire de travail actuel
static bool	init_wds(t_data *data)
{
	char	buff[PATH_MAX];
	char	*wd;

	wd = getcwd(buff, PATH_MAX);
	data->wdir = ft_strdup(wd);
	if (!data->wdir)
		return (false);
	if (venv_index(data->env, "OLDPWD") != -1)
	{
		data->old_wdir = ft_strdup(venv_value(data->env, "OLDPWD"));
		if (!data->old_wdir)
			return (false);
	}
	else
	{
		data->old_wdir = ft_strdup(wd);
		if (!data->old_wdir)
			return (false);
	}
	return (true);
}

// Initialise les données principales du shell
// Configure l'env, les répertoires de travail, et les structures de commande
// Gère les erreurs d'initialisation et configure les valeurs par défaut
bool	init_data(t_data *data, char **env)
{
	if (!init_venv(data, env))
	{
		errmsg_cmd("Fatal", NULL, "Could not initialize environment", FAILURE);
		return (false);
	}
	if (!init_wds(data))
	{
		errmsg_cmd("Fatal", NULL, "Could'nt initialize working directories", 1);
		return (false);
	}
	data->token = NULL;
	data->user_input = NULL;
	data->cmd = NULL;
	data->pid = -1;
	g_exit_status = SUCCESS;
	return (true);
}

// Initialise les structures d'input/output pour les commandes.
// Prépare le shell pour gérer les redirections d'entrée/sortie et les heredocs
void	init_io(t_cmd *cmd)
{
	if (!cmd->io_fds)
	{
		cmd->io_fds = malloc(sizeof * cmd->io_fds);
		if (!cmd->io_fds)
			return ;
		cmd->io_fds->infile = NULL;
		cmd->io_fds->outfile = NULL;
		cmd->io_fds->hdc_delimiter = NULL;
		cmd->io_fds->hdc_quotes = false;
		cmd->io_fds->fd_in = -1;
		cmd->io_fds->fd_out = -1;
		cmd->io_fds->stdin_copy = -1;
		cmd->io_fds->stdout_copy = -1;
	}
}
