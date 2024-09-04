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
	i = -1;
	while (++i < ft_tablen(shell->env))
		printf("%s\n", shell->env[i]);
	printf("%s\n", shell->path);
}
static void	init_value(t_mini *shell)
{
	shell->input = NULL;
	shell->token = NULL;
	shell->tlen = 0;
}

/*static void	exec(t_mini *shell)
{
	char	**tab;
	int	i;
	int	j;
	int	k;
	int	b;

	i = -1;
	j = 0;
	k = -1;
	b = 0;
	while (++i < shell->tlen)
	{
		if (shell->token[i].type == CMD)
		{
			while (i + j < shell->tlen && shell->token[i + j].type != OPERATOR)
				j++;
			tab = malloc(sizeof (char *) * (j + 1));
			while (++k < j)
				tab[k] = shell->token[i + b++].value;
			tab[k] = NULL;
			j++;
			//j = execve(shell->token[i].path_bin, tab, NULL);
			free(tab);
		}
	}
}*/

static void	minishell(t_mini *shell)
{
	while (1)
	{
		/* pour gérer CTRL + C , D et \ */ 
		signal_handler();
		init_value(shell);
		//le prompt pour récupérer l'input user
		shell->input = readline("minishell$ ");
		//pour gérer CTRL + D qui envoie une input (null)
		if (shell->input == NULL)
		{
			ft_free(shell, NULL, 0);
			exit(0);
		}
		shell->input[ft_strlen(shell->input)] = '\0';
		if (init_shell(shell) == FALSE)
			ft_free(shell, NULL, 0);
		else
		{	
			// fonction pour pouvoir réafficher les inputs avec fleche du haut/bas
			add_history(shell->input);
			tokenize(shell);
			print_token(shell);
			//exec(shell);
			ft_free(shell, NULL, 0);
		}
	}
	rl_clear_history();
}

int 	main(int ac, char **av, char **envp)
{
	t_mini	shell;
	(void)ac;
	(void)av;
	shell.env = ft_tabdup(envp);
	if (!shell.env)
		return (ft_free(&shell, strerror(errno), 1));
	//pour avoir le path actuel
	if (getcwd(shell.path, 4096) == NULL)
		return (ft_free(&shell, strerror(errno), 1));
	shell.path[ft_strlen(shell.path)] = '\0';
	minishell(&shell);
	return (1);
}