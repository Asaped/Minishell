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

static void	free_tab(char **tab)
{
	int	len;
	int	i;

	len = ft_tablen(tab);
	i = -1;
	while (++i < len)
	{
		if (tab[i])
			free(tab[i]);
	}
	if (tab != NULL)
		free(tab);
}

static void	free_token(t_token *token, int tlen)
{
	int	i;

	i = -1;
	while (++i < tlen)
	{
		if (token[i].value)
			free(token[i].value);
	}
	if (token != NULL)
		free(token);
}

static t_bool	ft_free(t_mini *shell, int error)
{
	if (shell->input != NULL)
		free(shell->input);
	if (shell->env != NULL && error != 0)
		free_tab(shell->env);
	if (shell->token != NULL)
		free_token(shell->token, shell->tlen);
	if (error != 0 && error != 10)
		return (ft_error(error));
	return (TRUE);
}

int 	main(int ac, char **av, char **envp)
{
	t_mini	shell;

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
			ft_free(&shell, 0);
		}
	}
	rl_clear_history();
	return (1);
}