/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:34:19 by nigateau          #+#    #+#             */
/*   Updated: 2025/01/20 20:34:19 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	increment_shlvl(t_mini *shell)
{
	char	**tmp;
	int		lvl;
	int		pos;

	pos = get_env_index(shell->env, "SHLVL");
	if (pos == -1)
	{
		shell->env = set_env_var(shell->env, "SHLVL", "2");
	}
	else
	{
		tmp = get_key_and_value(shell->env[pos]);
		lvl = ft_atoi(tmp[1]);
		lvl++;
		free(tmp[1]);
		tmp[1] = ft_itoa(lvl);
		shell->env = set_env_var(shell->env, tmp[0], tmp[1]);
		free_tab(tmp);
	}
}

int	init_shell(t_mini *shell, int first_time, char **envp)
{
	char	path[4096];

	if (first_time == 1)
	{
		shell->env = ft_tabdup(envp);
		if (!shell->env)
			return (ft_free(shell, strerror(errno), 1));
		shell->path = getcwd(path, 4096);
		if (!shell->path)
			return (ft_free(shell, strerror(errno), 1));
		shell->path = ft_strdup(shell->path);
		if (!shell->path)
			return (ft_free(shell, strerror(errno), 1));	
		if (get_env_value(shell, "PWD", 0) == NULL)
			shell->env = set_env_var(shell->env, "PWD", shell->path);
		increment_shlvl(shell);
	}
	shell->input = NULL;
	shell->token = NULL;
	shell->cmd = NULL;
	shell->clen = 0;
	shell->tlen = 0;
	shell->pid = -1;
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
