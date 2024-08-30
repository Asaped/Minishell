#include "../../incs/minishell.h"

char    *get_env_value(t_mini *shell, char *str)
{
    int i;
    int len;

    i = 0;
    len = ft_tablen(shell->env);
    while (i < len)
    {
        if (ft_strncmp(shell->env[i], str, ft_strlen(str)) == 0)
            return (shell->env[i] + ft_strlen(str) + 1);
        i++;
    }
    return (NULL);
}