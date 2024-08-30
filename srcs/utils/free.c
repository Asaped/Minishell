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

void	free_tab(char **tab)
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

void	free_token(t_token *token, int tlen)
{
	int	i;

	i = -1;
	while (++i < tlen)
	{
		if (token[i].value)
			free(token[i].value);
		if (token[i].path_bin)
			free(token[i].path_bin);
	}
	if (token != NULL)
		free(token);
}

t_bool	ft_free(t_mini *shell, int error)
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