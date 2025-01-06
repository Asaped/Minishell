#include "../../incs/minishell.h"

t_bool ft_env(char **env, t_cmd *cmd, int export_mode)
{
    int i;
    int len;

	i = -1;
    len = ft_tablen(env);
    if (cmd->tlen > 1)
	{
        return (ft_error("env: "), ft_error(cmd->token[1]), ft_error(":No such file or directory"), TRUE);
	}
	if (len <= 0)
	{
        return (ft_error("env: environment not set\n"), TRUE);
	}
    while (++i < len)
    {
        if (export_mode)
            ft_putstr_fd("export ", STDOUT_FILENO);
        ft_putendl_fd(env[i], STDOUT_FILENO);
    }
    return (FALSE);
}