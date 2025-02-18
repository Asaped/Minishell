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
		f_printf(STDERR_FILENO, "bash: ", cmd->output,
			": No such file or directory");
	}
	return (TRUE);
}

int	handle_input(t_token *token, t_cmd *cmd, int i)
{
	cmd->input = ft_strdup(token[i + 1].value);
	if (!cmd->input)
		return (ft_error(strerror(errno)));
	cmd->fd_in = open(cmd->input, O_RDONLY);
	if (cmd->fd_in == -1)
	{
		g_exit_status = errno;
		f_printf(STDERR_FILENO, "bash: ", cmd->input, ": No such file or directory");
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

static char	*ft_readline(void)
{
	char	*line;

	line = readline("> ");
	if (g_exit_status == SIGINT)
	{
		g_exit_status = SIGINT + 128;
		return (NULL);
	}
	if (g_exit_status == SIGQUIT)
	{
		g_exit_status = SIGQUIT + 128;
		return (NULL);
	}
	return (line);
}

static int	do_nothing(void)
{
	return (0);
}

static int	set_heredoc(t_mini *shell, t_cmd *cmd)
{
	char	*str;
	int		fd;

	fd = open(cmd->input, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (ft_error(strerror(errno)));
	signal_handler_interactive_heredoc();
	rl_event_hook = do_nothing;
	while (1)
	{
		str = ft_readline();
		if (str == NULL)
			break;
		if (!set_heredoc2(shell, cmd, str, fd))
		{
			free(str);
			break ;
		}
		free(str);
	}
	close(fd);
	return (TRUE);
}

int	handle_heredoc(t_mini *shell, t_token *token, t_cmd *cmd, int i)
{
	cmd->heredoc_key = ft_strdup(token[i + 1].value);
	if (!cmd->heredoc_key)
		return (ft_error(strerror(errno)));
	cmd->input = get_heredoc_name();
	if (!cmd->input)
		return (ft_error(strerror(errno)));
	if (set_heredoc(shell, cmd) == TRUE)
		cmd->fd_in = open(cmd->input, O_RDONLY);
	else
		cmd->fd_in = -1;
	return (TRUE);
}
