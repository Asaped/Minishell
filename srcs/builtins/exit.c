#include "../../incs/minishell.h"

static int    check_out_of_range(int neg, unsigned long long num, int *error)
{
    if ((neg == 1 && num > LONG_MAX)
        || (neg == -1 && num > -(unsigned long)LONG_MIN))
        *error = 1;
    return (*error);
}

static unsigned long long	ft_ull_atoi(const char *str, int *error)
{
    unsigned long long    num;
    int                    neg;
    int                    i;

    num = 0;
    neg = 1;
    i = 0;
    while (str[i] && is_whitespace(str[i]))
        i++;
    if (str[i] == '+')
        i++;
    else if (str[i] == '-')
    {
        neg *= -1;
        i++;
    }
    while (str[i] && ft_isdigit(str[i]))
    {
        num = (num * 10) + (str[i] - '0');
        if (check_out_of_range(neg, num, error))
            break ;
        i++;
    }
    return (num * neg);
}

static int	get_exit_code(char *error_code, int *error)
{
	int					i;
	unsigned long long	code;

	i = 0;
	if (!error_code)
		return (0); //g_exit_code
	while (error_code[i] && is_whitespace(error_code[i]))
		i++;
	if (error_code[i] == '+' && error_code[i] == '-')
		i++;
	while (error_code[i] && error_code[i] >= '0' && error_code[i] <= '9')
		i++;
	while (error_code[i] && is_whitespace(error_code[i]))
		i++;
	if (error_code[i])
		*error = 1;
	code = ft_ull_atoi(error_code, error);
	return (code % 256);
}

t_bool ft_exit(t_mini *shell, char **token)
{
	int	error;

	error = 0;
	if (shell->cmd[1].token == NULL)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (token[1] && token[2])
		return (ft_error("bash: exit: too many arguments\n"), TRUE);
	if (!token[1])
		g_exit_status = 0;
	else
	{
		g_exit_status = get_exit_code(token[1], &error);
		if (error == 1)
			return (ft_error("bash: exit: "), ft_error(token[1]), ft_error(": numeric argument required\n"), TRUE);
	}
	ft_free(shell, NULL, 1);
	exit(g_exit_status);
	return (FALSE);
}