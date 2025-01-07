/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.lausanne>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:57:37 by nigateau          #+#    #+#             */
/*   Updated: 2025/01/07 21:02:20 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int exec_builtin(t_cmd *cmd, t_mini *shell)
{
    if (!ft_strncmp(cmd->token[0], "echo", ft_strlen("echo")))
        return ft_echo(cmd);
    if (!ft_strncmp(cmd->token[0], "cd", ft_strlen("cd")))
        return ft_cd(shell, cmd);
    if (!ft_strncmp(cmd->token[0], "pwd", ft_strlen("pwd")))
        return ft_pwd();
    if (!ft_strncmp(cmd->token[0], "export", ft_strlen("export")))
        return ft_export(shell, cmd);
    if (!ft_strncmp(cmd->token[0], "unset", ft_strlen("unset")))
        return ft_unset(shell, cmd);
    if (!ft_strncmp(cmd->token[0], "env", ft_strlen("env")))
        return ft_env(shell->env, cmd, 0);
    if (!ft_strncmp(cmd->token[0], "exit", ft_strlen("exit")))
        return ft_exit(shell, cmd);
    return 0;
}

void update_exit_status(int status)
{
    if (WIFEXITED(status))
        g_exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        g_exit_status = 128 + WTERMSIG(status);
}

void execute_builtin(t_cmd *cmd, t_mini *shell, int *prev_fd, int i)
{
    int saved_stdout;
    int saved_stdin;

    saved_stdin = dup(STDIN_FILENO);
    saved_stdout = dup(STDOUT_FILENO);

    if (cmd->output || cmd->input)
        setup_redirections(cmd);
    if (i < shell->clen - 1)
    {
        if (pipe(cmd->fd_pipe) == -1)
        {
            perror("Error with pipe");
            g_exit_status = errno;
            restore_stdin_stdout(saved_stdin, saved_stdout);
            exit(EXIT_FAILURE);
        }
        if (dup2(cmd->fd_pipe[1], STDOUT_FILENO) == -1)
        {
            perror("Error with dup2");
            g_exit_status = errno;
            exit(EXIT_FAILURE);
        }
        close(cmd->fd_pipe[1]);
        *prev_fd = cmd->fd_pipe[0];
    }
    g_exit_status = exec_builtin(cmd, shell);
    restore_stdin_stdout(saved_stdin, saved_stdout);
}

void    restore_stdin_stdout(int std_in, int std_out)
{
    dup2(std_out, STDOUT_FILENO);
    dup2(std_in, STDIN_FILENO);
    close(std_out);
    close(std_in);
    return;
}
