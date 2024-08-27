#include "../../incs/minishell.h"

t_bool	ft_error(int error)
{
	if (error == 1)
		printf("Error : unclosed quote\n");
	else if (error == 2)
		printf("Syntax error near unexpected token \'|\'\n");
	else if (error == 3)
		printf("Malloc error.\n");
	return (FALSE);
}