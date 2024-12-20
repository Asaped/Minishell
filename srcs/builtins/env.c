#include "../../incs/minishell.h"

t_bool ft_env(char **env, char **token, int export_mode)
{
    int i;

	i = 0;
    if (token != NULL && token[1])
	{
        return (ft_error("env: too many arguments\n"));
	}
	if (!env)
	{
        return (ft_error("env: environment not set\n"));
	}
    while (env[i])
    {
        if (export_mode)
            ft_putstr_fd("export ", STDOUT_FILENO);
        ft_putendl_fd(env[i++], STDOUT_FILENO);
    }
    return (TRUE);
}