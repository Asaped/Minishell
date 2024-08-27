#include "../../incs/minishell.h"

static int	ft_tablen(char **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

static char	**ft_tabdup(char **src)
{
	char	**dest;
	int		i;
	int		count;

	i = 0;
	count = ft_tablen(src);
	dest = malloc(sizeof(char *) * count);
	if (!dest)
		return (NULL);
	while (i < count)
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
			return (NULL);
		i++;
	}
	return (dest);
}

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
		else if (shell->token[i].type == $)
			printf("TYPE = DOLLAR\n");
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
	/*i = -1;
	while (++i < ft_tablen(shell->env))
		printf("%s\n", shell->env[i]);
	printf("%s\n", shell->path);*/
}

static void	handle_sigint(int sig)
{
	(void)sig;
	rl_redisplay();
	printf("  \b");
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	signal_handler(void)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	sigint.sa_handler = handle_sigint;
	sigemptyset(&sigint.sa_mask);
	sigint.sa_flags = 0;
	sigaction(SIGINT, &sigint, NULL);
	sigquit.sa_handler = SIG_IGN;
	sigemptyset(&sigquit.sa_mask);
	sigquit.sa_flags = 0;
	sigaction(SIGQUIT, &sigquit, NULL);
}

int 	main(int ac, char **av, char **envp)
{
	t_mini	shell;

	shell.env = ft_tabdup(envp);
	if (!shell.env)
		return (ft_error(3));
	while (1)
	{
		signal_handler();
		shell.input = readline("minishell$ ");
		if (!init_shell(&shell))
			return (0);
		printf("input = \"%s\"\n", shell.input);
		add_history(shell.input);
		tokenize(&shell);
		print_token(&shell);
	}
	return (1);
}