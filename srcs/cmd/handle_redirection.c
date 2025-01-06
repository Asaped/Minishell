#include "../../incs/minishell.h"

t_bool	handle_output(t_token *token, t_cmd *cmd, int i)
{
	cmd->output = ft_strdup(token[i + 1].value);
	if (!cmd->output)
		return (ft_error(strerror(errno)), ft_error("\n"));
	if (token[i].value[1] == '>')
		cmd->fd_out = open(cmd->output, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		cmd->fd_out = open(token[i + 1].value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->fd_out == -1)
		return (ft_error(strerror(errno)), ft_error("\n"));
	return (TRUE);
}

t_bool	handle_input(t_token *token, t_cmd *cmd, int i)
{
	cmd->input = ft_strdup(token[i + 1].value);
	if (!cmd->input)
		return (ft_error(strerror(errno)), ft_error("\n"));
	cmd->fd_in = open(cmd->input, O_RDONLY);
	if (cmd->fd_in == -1)
		return (ft_error(strerror(errno)), ft_error("\n"));
	return (TRUE);
}

static char	*get_heredoc_name(void)
{
	static int	i = 0;
	char		*name;
	char		*tmp;

	tmp = ft_itoa(i);
	if (!tmp)
		return (NULL);
	name = ft_strjoin4("/tmp/.heredoc_", tmp);
	i++;
	return (name);
}

static t_bool set_heredoc(t_mini *shell, t_cmd *cmd)
{
	char	*str;
	int		fd;

	fd = open(cmd->input, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (ft_error(strerror(errno)), ft_error("\n"));
	while (1)
	{
		signal_handler_interactive();
		str = readline("> ");
		signal_handler_non_interactive();
		if (str == NULL || !ft_strncmp(str, cmd->heredoc_key, ft_strlen(cmd->heredoc_key)))
			break ;
		if (ft_strchr(str, '$'))
		{
			str = expand_env(shell, str);
			ft_putendl_fd(str, fd);
		}
		else
		{
			ft_putendl_fd(str, fd);
			free(str);
		}
	}
	free(str);
	close(fd);
	return (TRUE);
}

t_bool	handle_heredoc(t_mini *shell, t_token *token, t_cmd *cmd, int i)
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