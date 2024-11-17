#include "../../incs/minishell.h"

t_bool ft_pwd(void)
{
    char    path[4096];

    if (getcwd(path, 4096) == NULL)
        return (ft_error(strerror(errno)));
    ft_putendl_fd(path, STDOUT_FILENO);
    return (TRUE);
}