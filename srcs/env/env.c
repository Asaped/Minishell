#include "../../incs/minishell.h"

char    *get_env_value(t_mini *shell, char *str, int malloc)
{
    int i;
    int len;

    i = 0;
    len = ft_tablen(shell->env);
    while (i < len)
    {
        if (shell->env[i][ft_strlen(str)] == '=' && ft_strncmp(shell->env[i], str, ft_strlen(str)) == 0)
        {
            len = ft_strlen(str);
            if (malloc == 1)
                free(str);
            return (shell->env[i] + len + 1);
        }
        i++;
    }
    if (malloc == 1)
        free(str);
    return (NULL);
}