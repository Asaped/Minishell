#include "../../incs/minishell.h"

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

static void	free_cmd(t_cmd *cmd, int clen)
{
	int	i;

	i = -1;
	while (++i < clen)
	{
		if (cmd[i].token)
			free(cmd[i].token);
		if (cmd[i].heredoc_key)
		{
			free(cmd[i].heredoc_key);
			if (cmd[i].input)
				unlink(cmd[i].input);
		}
		if (cmd[i].input)
			free(cmd[i].input);
		if (cmd[i].output)
			free(cmd[i].output);
		if (cmd[i].fd_in != -1)
			close(cmd[i].fd_in);
		if (cmd[i].fd_out != -1)
			close(cmd[i].fd_out);
	}
	free(cmd);
}

t_bool	ft_free(t_mini *shell, char *error, int flag)
{
	if (shell->input != NULL)
		free(shell->input);
	if (shell->cmd != NULL)
		free_cmd(shell->cmd, shell->clen);
	if (shell->token != NULL)
		free_token(shell->token, shell->tlen);
	if (shell->env != NULL && flag)
		free_tab(shell->env);
	if (shell->path != NULL && flag)
		free(shell->path);
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