#include "../../incs/minishell.h"

t_bool is_n_option(char *str)
{
    int i;

    i = 0;
    if (str[i] == '-')
        i++;
    while (str[i] && str[i] == 'n')
        i++;
    if (!str[i])
        return (TRUE);
    return (FALSE);
}

t_bool ft_echo(char **token)
{
    int i;
    int is_n;

    is_n = 0;
    if (token[1])
        is_n = is_n_option(token[1]);
    if (is_n && token[1])
        i = 1;
    else
        i = 0;
    while (token[++i])
    {
        ft_putstr_fd(token[i], STDOUT_FILENO);
        if (token[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
    }
	if (!is_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (FALSE);
}