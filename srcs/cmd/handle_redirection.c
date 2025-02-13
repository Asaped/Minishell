/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:51:53 by nigateau          #+#    #+#             */
/*   Updated: 2025/01/20 20:51:53 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	handle_output(t_token *token, t_cmd *cmd, int i)
{
	cmd->output = ft_strdup(token[i + 1].value);
	if (!cmd->output)
		return (ft_error(strerror(errno)));
	if (token[i].value[1] == '>')
		cmd->fd_out = open(cmd->output, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		cmd->fd_out = open(token[i + 1].value, O_CREAT | O_WRONLY | O_TRUNC,
				0644);
	if (cmd->fd_out == -1)
	{
		g_exit_status = errno;
		fprintf(stderr, "bash: %s: No such file or directory\n", cmd->output);
	}
	return (TRUE);
}

int	handle_input(t_token *token, t_cmd *cmd, int i)
{
	cmd->input = ft_strdup(token[i + 1].value);
	if (!cmd->input)
		return (ft_error(strerror(errno)), ft_error("\n"));
	cmd->fd_in = open(cmd->input, O_RDONLY);
	if (cmd->fd_in == -1)
	{
		g_exit_status = errno;
		fprintf(stderr, "bash: %s: No such file or directory\n", cmd->input);
	}
	return (TRUE);
}

static char	*get_heredoc_name(void)
{
	static int	i;
	char		*name;
	char		*tmp;

	i = 0;
	tmp = ft_itoa(i);
	if (!tmp)
		return (NULL);
	name = ft_strjoin4("/tmp/.heredoc_", tmp);
	i++;
	return (name);
}

static int	set_heredoc(t_mini *shell, t_cmd *cmd)
{
	char	*str;
	int		fd;

	fd = open(cmd->input, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (ft_error(strerror(errno)), ft_error("\n"));
	rl_done = 0;
	while (1)
	{
		signal_handler_interactive();
		str = readline("> ");
		signal_handler_non_interactive();
		if (!set_heredoc2(shell, cmd, str, fd))
			break ;
	}
	free(str);
	close(fd);
	return (TRUE);
}

int	handle_heredoc(t_mini *shell, t_token *token, t_cmd *cmd, int i)
{
	cmd->heredoc_key = ft_strdup(token[i + 1].value);
	if (!cmd->heredoc_key)
		return (ft_error(strerror(errno)), ft_error("\n"));
	cmd->input = get_heredoc_name();
	if (!cmd->input)
		return (ft_error(strerror(errno)), ft_error("\n"));
	if (set_heredoc(shell, cmd) == TRUE)
		cmd->fd_in = open(cmd->input, O_RDONLY);
	else
		cmd->fd_in = -1;
	return (TRUE);
}
