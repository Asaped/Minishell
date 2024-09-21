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
		else if (shell->token[i].type == STRING)
			printf("TYPE = STRING\n");
		else if (shell->token[i].type == OPERATOR)
			printf("TYPE = OPERATOR\n");
		else if (shell->token[i].type == UNKNOWN)
			printf("TYPE = UNKNOWN\n");
		if (shell->token[i].path_bin != NULL)
			printf("PATH_BIN = \"%s\"\n", shell->token[i].path_bin);
		printf("VALUE = \"%s\"\n", shell->token[i].value);
		printf("LEN = %d\n\n", shell->token[i].len);
	}
	/*i = -1;
	while (++i < ft_tablen(shell->env))
		printf("%s\n", shell->env[i]);*/
	printf("%s\n", shell->path);
}

static void	exec(t_mini *shell)
{
	/*char	**tab;
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
	}*/
}

static void	init_value(t_mini *shell)
{
	shell->input = NULL;
	shell->token = NULL;
	shell->cmd = NULL;
	shell->clen = 0;
	shell->tlen = 0;
}

static int	get_token_length(t_token *token, int i, int tlen)
{
	int	count;

	count = 0;
	while (++i < tlen)
	{
		if (token[i].type == OPERATOR && token[i].value[0] == '|')
			return (count);
		count++;
	}
	return (count);
}

static int	get_command(t_cmd *cmd, t_token *token, int *j, int tlen)
{
	int		i;

	i = -1;
	cmd->tlen = get_token_length(token, j[0] - 1, tlen);
	cmd->token = malloc(sizeof(t_token) * cmd->tlen);
	if (!cmd->token)
		return (ft_error(strerror(errno)));
	while (++i < cmd->tlen)
		cmd->token[i] = token[j[0]++];
	if (token[j[0]].type == OPERATOR)
		j[0]++;
	cmd->fd_bracket = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 0;
	return (TRUE);
}

static int	pipe_count(t_token *token, int tlen)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < tlen)
		if (token[i].value[0] == '|')
			count++;
	return (count);
}

static int	get_command_tab(t_mini *shell)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	shell->clen = pipe_count(shell->token, shell->tlen) + 1;
	shell->cmd = malloc(sizeof(t_cmd) * shell->clen);
	if (!shell->cmd)
		return (ft_error(strerror(errno)));
	while (++i < shell->clen)
		get_command(&shell->cmd[i], shell->token, &j, shell->tlen);
	i = -1;
	while (++i < shell->clen)
	{
		j = -1;
		printf("-----command[%d]-----\n", i);
		printf("token len = %d\n", shell->cmd[i].tlen);
		while (++j < shell->cmd[i].tlen)
			printf("token[%d] = \"%s\"\n", j, shell->cmd[i].token[j].value);
		printf("fd_bracket value = %d\n", shell->cmd[i].fd_bracket);
		printf("fd_in value = %d\n", shell->cmd[i].fd_in);
		printf("fd_out value = %d\n", shell->cmd[i].fd_out);
		printf("-----command[%d]-----\n\n", i);
	}
	return (TRUE);
}

static void	minishell(t_mini *shell)
{
	while (1)
	{
		signal_handler();
		init_value(shell);
		shell->input = readline("minishell$ ");
		if (shell->input == NULL)
		{
			ft_free(shell, NULL, 0);
			exit(0);
		}
		shell->input[ft_strlen(shell->input)] = '\0';
		if (init_shell(shell) == FALSE || tokenize(shell) == FALSE)
			ft_free(shell, NULL, 0);
		else
		{	
			print_token(shell);
			get_command_tab(shell);
			exec(shell);
			ft_free(shell, NULL, 0);
		}
	}
	rl_clear_history();
	ft_free(shell, NULL, 1);
}

int 	main(int ac, char **av, char **envp)
{
	t_mini	shell;
	(void)ac;
	(void)av;
	shell.env = ft_tabdup(envp);
	if (!shell.env)
		return (ft_free(&shell, strerror(errno), 1));
	if (getcwd(shell.path, 4096) == NULL)
		return (ft_free(&shell, strerror(errno), 1));
	shell.path[ft_strlen(shell.path)] = '\0';
	minishell(&shell);
	return (1);
}