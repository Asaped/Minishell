#include "../../incs/minishell.h"

t_bool	init_shell(t_mini *shell, int first_time, char **envp)
{
	if (first_time == 1)
	{
		shell->env = ft_tabdup(envp);
		if (!shell->env)
			return (ft_free(shell, strerror(errno), 1));
		if (getcwd(shell->path, 4096) == NULL)
			return (ft_free(shell, strerror(errno), 1));
		shell->path[ft_strlen(shell->path)] = '\0';
	}
	shell->input = NULL;
	shell->token = NULL;
	shell->cmd = NULL;
	shell->clen = 0;
	shell->tlen = 0;
	return (TRUE);
}

void	init_cmd(t_cmd *cmd)
{
	cmd->token = NULL;
	cmd->path_bin = NULL;
	cmd->heredoc_key = NULL;
	cmd->input = NULL;
	cmd->output = NULL;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	cmd->tlen = 0;
	cmd->fd_pipe[0] = -1;
	cmd->fd_pipe[1] = -1;
}
