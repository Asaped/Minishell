#include "../../incs/minishell.h"

static void print_token(t_mini *shell)
{
	int		i = -1;

	printf("\n");
	printf("INPUT = \"%s\"\n", shell->input);
	printf("\n");
	while (++i < shell->tlen)
	{
		if (shell->token[i].type == BUILTIN)
			printf("TYPE = BUILTIN\n");
		else if (shell->token[i].type == CMD)
			printf("TYPE = CMD\n");
		else if (shell->token[i].type == $)
			printf("TYPE = DOLLAR\n");
		else if (shell->token[i].type == FICHIER)
			printf("TYPE = FICHIER\n");
		else if (shell->token[i].type == STRING)
			printf("TYPE = STRING\n");
		else if (shell->token[i].type == OPTIONN)
			printf("TYPE = OPTION -n\n");
		else if (shell->token[i].type == OPERATOR)
			printf("TYPE = OPERATOR\n");
		else if (shell->token[i].type == UNKNOWN)
			printf("TYPE = UNKNOWN\n");
		if (shell->token[i].path_bin != NULL)
			printf("PATH_BIN = \"%s\"\n", shell->token[i].path_bin);
		printf("POS = %i\nVALUE = \"%s\"\n\n", shell->token[i].original_pos, shell->token[i].value);
	}
	/*i = -1;
	while (++i < ft_tablen(shell->env))
		printf("%s\n", shell->env[i]);*/
	printf("%s\n", shell->path);
}

int 	main(int ac, char **av, char **envp)
{
	t_mini	shell;
	int i = -1;
	int j = 4242;
	char	**tab;
	(void)ac;
	(void)av;
	shell.env = ft_tabdup(envp);
	if (!shell.env)
		return (ft_free(&shell, 3));
	while (1)
	{
		shell.input = NULL;
		shell.token = NULL;
		signal_handler();
		shell.input = readline("minishell$ ");
		if (shell.input == NULL)
		{
			ft_free(&shell, 10);
			exit(0);
		}
		if (init_shell(&shell) == FALSE)
			ft_free(&shell, 0);
		else
		{	
			add_history(shell.input);
			tokenize(&shell);
			print_token(&shell);
			while (++i < shell.tlen)
			{
				if (shell.token[i].type == CMD)
				{
					tab = ft_split(shell.token[i].value, ' ');
					printf("dsafa\n");
					j = execve(shell.token[i].path_bin, tab, NULL);
					printf("%d\n", j);
				}
			}
			ft_free(&shell, 0);
		}
	}
	rl_clear_history();
	return (1);
}