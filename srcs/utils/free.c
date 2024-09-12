#include "../../incs/minishell.h"

void	free_tab(char **tab)
{
	int	len;
	int	i;

	len = ft_tablen(tab);
	i = -1;
	while (++i < len)
	{
		printf("free_tab\n");
		if (tab[i])
			free(tab[i]);
		printf("freed_tab\n");
	}
	if (tab != NULL)
		free(tab);
}

void	free_token(t_token *token, int tlen)
{
	int	i;

	i = -1;
	while (++i < tlen)
	{
		printf("free_token[%d]\n", i);
		if (token[i].value)
			free(token[i].value);
		printf("freed_token_value\n");
		if (token[i].path_bin)
			free(token[i].path_bin);
		printf("freed_path_bin\n");
	}
	if (token != NULL)
		free(token);
}

t_bool	ft_free(t_mini *shell, char *error, int flag)
{
	if (shell->input != NULL)
		free(shell->input);
	if (shell->token != NULL)
		free_token(shell->token, shell->tlen);
	if (shell->env != NULL && flag)
		free_tab(shell->env);
	if (error)
		return (ft_error(error));
	return (FALSE);
}

t_bool	ft_error(char *error)
{
	write(STDERR_FILENO, error, ft_strlen(error));
	errno = 0;
	return (FALSE);
}