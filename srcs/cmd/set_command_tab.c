#include "../../incs/minishell.h"

static void	close_open_fd(t_cmd *cmd, int mode)
{
	if (mode == 1)
	{
		if (cmd->output != NULL)
		{
			free(cmd->output);
			cmd->output = NULL;
		}
		if (cmd->fd_out != -1)
		{
			close(cmd->fd_out);
			cmd->fd_out = -1;
		}
	}
	else if (mode == 2)
	{
		if (cmd->heredoc_key != NULL)
		{
			free(cmd->heredoc_key);
			cmd->heredoc_key = NULL;
			if (cmd->input != NULL)
				unlink(cmd->input);
		}
		if (cmd->input != NULL)
		{
			free(cmd->input);
			cmd->input = NULL;
		}
		if (cmd->fd_in != -1)
		{
			close(cmd->fd_in);
			cmd->fd_in = -1;
		}
	}
}

static t_bool	set_io(t_mini *shell, t_cmd *cmd, t_token *token, int i)
{
	while (++i < shell->tlen && !is_pipe(token[i]))
	{
		if (token[i].type == OPERATOR && token[i].value[0] == '>')
		{
			if (cmd->output != NULL)
			close_open_fd(cmd, 1);
			if (handle_output(token, cmd, i) == FALSE)
				return (FALSE);
		}
		else if (token[i].type == OPERATOR && token[i].value[0] == '<')
		{
			if (cmd->input != NULL)
				 close_open_fd(cmd, 2);
			if (token[i].value[1] == '<')
			{
				if (handle_heredoc(shell, token, cmd, i) == FALSE)
					return (FALSE);
			}
			else
				if (handle_input(token, cmd, i) == FALSE)
					return (FALSE);
		}
	}
	return (TRUE);
}

static t_bool	get_command(t_mini *shell, t_cmd *cmd, t_token *token, int *j)
{
	int		i;

	i = 0;
	init_cmd(cmd);
	if (set_io(shell, cmd, token, j[0] - 1) == FALSE)
		return (FALSE);
	cmd->tlen = get_token_length(token, j[0] - 1, shell->tlen);
	cmd->token = malloc(sizeof(char *) * (cmd->tlen + 1));
	if (!cmd->token)
		return (ft_error(strerror(errno)));
	cmd->token[cmd->tlen] = NULL;
	if (token[j[0]].type == OPERATOR && token[j[0]].value[0] != '|')
			j[0] += 2;
	while (i < cmd->tlen)
	{
		if (token[j[0]].path_bin != NULL && cmd->path_bin == NULL)
			cmd->path_bin = token[j[0]].path_bin;
		if (token[j[0]].type != OPERATOR)
			cmd->token[i++] = token[j[0]++].value;
		if (token[j[0]].type == OPERATOR && token[j[0]].value[0] != '|')
			j[0] += 2;
	}
	cmd->token[i] = NULL;
	if (is_pipe(token[j[0]]))
		j[0]++;
	return (TRUE);
}

int	set_command_tab(t_mini *shell)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	shell->clen = pipelen(shell->token, shell->tlen) + 1;
	shell->cmd = malloc(sizeof(t_cmd) * (shell->clen + 1));
	if (!shell->cmd)
		return (ft_error(strerror(errno)));
	while (++i < shell->clen)
	{
		if (get_command(shell, &shell->cmd[i], shell->token, &j) == FALSE)
			return (FALSE);
	}
	shell->cmd[i].token = NULL;
	return (TRUE);
}
