/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:22:49 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/26 08:26:38 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	update_current_dir(t_data *data, char *wd)
{
	venv_set(data, "OLDPWD", venv_value(data->env, "PWD"));
	venv_set(data, "PWD", wd);
	if (data->old_wdir)
	{
		free_ptr(data->old_wdir);
		data->old_wdir = ft_strdup(data->wdir);
	}
	if (data->wdir)
	{
		free_ptr(data->wdir);
		data->wdir = ft_strdup(wd);
	}
	free_ptr(wd);
}

static bool	chdir_error(char *path)
{
	if (errno == ESTALE)
		errno = ENOENT;
	errmsg_cmd("cd", path, strerror(errno), errno);
	return (false);
}

static bool	change_dir(t_data *data, char *path)
{
	char	*ret;
	char	*tmp;
	char	cwd[PATH_MAX];

	ret = NULL;
	if (chdir(path) != SUCCESS)
		return (chdir_error(path));
	ret = getcwd(cwd, PATH_MAX);
	if (!ret)
	{
		errmsg_cmd("cd: error retrieving current directory",
			"getcwd: cannot access parent directories", strerror(errno), errno);
		ret = ft_strjoin(data->wdir, "/");
		tmp = ret;
		ret = ft_strjoin(tmp, path);
		free_ptr(tmp);
	}
	else
		ret = ft_strdup(cwd);
	update_current_dir(data, ret);
	return (true);
}

int	builtin_cd(t_data *data, char **args)
{
	char	*path;

	if (!args || !args[1] || ft_isspace(args[1][0]) || args[1][0] == '\0'
		|| ft_strncmp(args[1], "--", 3) == SUCCESS)
	{
		path = venv_value(data->env, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (errmsg_cmd("cd", NULL, "HOME not set", EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	if (args[2])
		return (errmsg_cmd("cd", NULL, "too many arguments", EXIT_FAILURE));
	if (ft_strncmp(args[1], "-", 2) == SUCCESS)
	{
		path = venv_value(data->env, "OLDPWD");
		if (!path)
			return (errmsg_cmd("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	return (!change_dir(data, args[1]));
}
