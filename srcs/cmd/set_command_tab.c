#include "../../incs/minishell.h"

static t_bool	set_io(t_mini *shell, t_cmd *cmd, t_token *token, int i)
{
	while (i < shell->tlen && !is_pipe(token[i]))
		i++;
	while (--i >= 0 && !is_pipe(token[i]))
	{
		if (is_pipe(token[i]))
			break ;
		if (token[i].type == OPERATOR && token[i].value[0] == '>' && cmd->output == NULL)
		{
			if (handle_output(token, cmd, i) == FALSE)
				return (FALSE);
		}
		else if (token[i].type == OPERATOR && token[i].value[0] == '<' && cmd->input == NULL)
		{
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
	if (set_io(shell, cmd, token, j[0]) == FALSE)
		return (FALSE);
	cmd->tlen = get_token_length(token, j[0] - 1, shell->tlen);
	cmd->token = malloc(sizeof(t_token) * cmd->tlen);
	if (!cmd->token)
		return (ft_error(strerror(errno)));
	if (token[j[0]].type == OPERATOR && token[j[0]].value[0] != '|')
			j[0] += 2;
	while (i < cmd->tlen)
	{
		if (token[j[0]].type != OPERATOR)
			cmd->token[i++] = token[j[0]++];
		if (token[j[0]].type == OPERATOR && token[j[0]].value[0] != '|')
			j[0] += 2;
	}
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
	shell->cmd = malloc(sizeof(t_cmd) * shell->clen);
	if (!shell->cmd)
		return (ft_error(strerror(errno)));
	while (++i < shell->clen)
	{
		if (get_command(shell, &shell->cmd[i], shell->token, &j) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}
