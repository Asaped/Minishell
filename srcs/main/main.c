#include "../../incs/minishell.h"

static void print_token(t_mini *shell)
{
	int		i = -1;

	printf("\n");
	printf("INPUT = \"%s\"\n", shell->input);
	printf("\n");
	while (++i < shell->tlen)
	{
		if (shell->token[i].type == CMD)
			printf("TYPE = CMD\n");
		else if (shell->token[i].type == DIR)
			printf("TYPE = DIR\n");
		else if (shell->token[i].type == STRING)
			printf("TYPE = STRING\n");
		else if (shell->token[i].type == OPTIONN)
			printf("TYPE = OPTION -n\n");
		else if (shell->token[i].type == OPERATOR)
			printf("TYPE = OPERATOR\n");
		else if (shell->token[i].type == UNKNOWN)
			printf("TYPE = UNKNOWN\n");
		printf("POS = %i\nVALUE = %s\n\n", shell->token[i].pos, shell->token[i].value);
	}
}

int 	main(int ac, char **av)
{
	t_mini	shell;

	av[1] = " >f.txt echo hi>> echo ha\"hi\" ho<<|<|bruh bruh bruh<<echo slt||echo bjr  ";

	if (ac > 1)
	{
		if (init_shell(&shell, av[1]))
			tokenize(&shell);
	}
	print_token(&shell);
	return (1);
}