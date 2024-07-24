#include "../../incs/minishell.h"

int	ft_error(int error)
{
	if (error == 1)
		printf("Error : unclosed quote\n");
	else if (error == 2)
		printf("Syntax error near unexpected token \'|\'\n");
	return (0);
}