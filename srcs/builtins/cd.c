#include "../../incs/minishell.h"

static t_bool  ft_is_dir(char *path)
{
    struct stat path_stat;

    if (stat(path, &path_stat) == 0)
    {
        if (S_ISDIR(path_stat.st_mode))
            return (TRUE);
        else
            return (ft_error("bash: cd: "), ft_error(path), ft_error(": Not a directory\n"));
    }
    else
        return (ft_error("bash: cd: "), ft_error(path), ft_error(": No such file or directory\n"));
}

static t_bool change_dir(t_mini *shell, char *path)
{
	char	tab[4096];

	if (chdir(path) == -1)
        return (ft_error(strerror(errno)), TRUE);
    if (shell->path)
	{
    	free(shell->path);
	}
	shell->path = getcwd(tab, 4096);
	if (!shell->path)
		return (ft_error("bash: cd: could not retrieve current directory\n"), TRUE);
	shell->path = ft_strdup(shell->path);
	if (!shell->path)
		return (ft_error("bash: cd: "), ft_error(strerror(errno)), ft_error("\n"), TRUE);
    shell->env = set_env_var(shell->env, "OLDPWD", get_env_value(shell, "PWD", 0));
	shell->env = set_env_var(shell->env, "PWD", shell->path);
    return (FALSE);
}

t_bool ft_cd(t_mini *shell, t_cmd *cmd)
{
    char    *path;

    path = NULL;
    if (cmd->tlen >= 3)
        return (ft_error("bash: cd: too many arguments\n"), TRUE);
    if (cmd->tlen <= 1 || !ft_strncmp(cmd->token[1], "-\0", 2) || !ft_strncmp(cmd->token[1], "~\0", 2) || !ft_strncmp(cmd->token[1], "--\0", 3))
    {
        path = get_env_value(shell, "HOME", 0);
        if (!path)
            return (ft_error("bash: cd: HOME not set\n"), TRUE);
    }
    else if (cmd->tlen == 2)
        path = cmd->token[1];
    if (ft_is_dir(path))
        return (change_dir(shell, path));
    else
        return (TRUE);
}