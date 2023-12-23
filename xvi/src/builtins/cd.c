/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 12:36:19 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 19:08:05 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	edit_chdir_errno(char *path)
{
	if (errno == ESTALE)
		errno = ENOENT;
	errmsg_cmd("cd", path, strerror(errno), errno);
	return (false);
}

static void	update_wdir(t_data *data, char *wdir)
{
	venv_set(data, "OLDPWD", venv_value(data->env, "PWD"));
	venv_set(data, "PWD", wdir);
	if (data->old_wdir)
	{
		free_ptr(data->old_wdir);
		data->old_wdir = ft_strdup(data->wdir);
	}
	if (data->wdir)
	{
		free_ptr(data->wdir);
		data->wdir = ft_strdup(wdir);
	}
	free_ptr(wdir);
	return ;
}

static bool	change_dir(t_data *data, char *path)
{
	char	*result;
	char	*tmp;
	char	cwd[PATH_MAX];

	result = NULL;
	if (chdir(path))
		return (edit_chdir_errno(path));
	result = getcwd(cwd, PATH_MAX);
	if (!result)
	{
		errmsg_cmd("cd: error retrieve current dir",
			"getcwd: no acess parent dir", strerror(errno), errno);
		result = ft_strjoin(data->wdir, "/");
		tmp = result;
		result = ft_strjoin(tmp, path);
		free_ptr(tmp);
	}
	else
		result = ft_strdup(cwd);
	update_wdir(data, result);
	return (true);
}

int	builtin_cd(t_data *data, char **args)
{
	char	*path;

	if (!args || !args[1] || ft_isspace(args[1][0]) || args[1][0] == '\0'
		|| ft_strncmp(args[1], "--", 3) == 0)
	{
		path = venv_value(data->env, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (errmsg_cmd("cd", NULL, "HOME not set", EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	if (args[2])
		return (errmsg_cmd("cd", NULL, "too many args", EXIT_FAILURE));
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = venv_value(data->env, "OLDPWD");
		if (!path)
			return (errmsg_cmd("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	return (!change_dir(data, args[1]));
}
