/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.lausanne>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:45:17 by nigateau          #+#    #+#             */
/*   Updated: 2024/12/20 16:37:26 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

// Gestion des pipes pour une commande donnée
void setup_pipes(t_cmd *cmd, int prev_fd, int is_last_cmd)
{
    if (prev_fd != -1)
        dup2(prev_fd, STDIN_FILENO);
    if (!is_last_cmd)
    {
        dup2(cmd->fd_pipe[1], STDOUT_FILENO);
        close(cmd->fd_pipe[0]);
        close(cmd->fd_pipe[1]);
    }
}

// Gestion des redirections d'entrée/sortie pour une commande
void setup_redirections(t_cmd *cmd)
{
    if (cmd->input)
        cmd->fd_in = open(cmd->input, O_RDONLY);
    if (cmd->output)
        cmd->fd_out = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (cmd->fd_in != -1)
        dup2(cmd->fd_in, STDIN_FILENO);
    if (cmd->fd_out != -1)
        dup2(cmd->fd_out, STDOUT_FILENO);
}

// Exécution d'une commande
void execute_command(t_cmd *cmd, char **env)
{
    if (access(cmd->path_bin, F_OK) == -1)
    {
        perror("Command not found");
        g_exit_status = 127;
        return;
    }
    if (access(cmd->path_bin, X_OK) == -1)
    {
        perror("Permission denied");
        g_exit_status = 126;
        return;
    }
    execve(cmd->path_bin, cmd->token, env);
    perror("execve");
    exit(EXIT_FAILURE);
}

// Fork et exécution d'une commande
void fork_and_execute(t_mini *shell, t_cmd *cmd, int prev_fd, int is_last_cmd)
{
    shell->pid = fork();
    if (shell->pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (shell->pid == 0)
    {
        setup_pipes(cmd, prev_fd, is_last_cmd);
        setup_redirections(cmd);
        execute_command(cmd, shell->env);
    }
}

// Pipeline principal
void execute_pipeline(t_mini *shell)
{
    int i = 0;
    int prev_fd = -1;
    int status = 0;

    while (i < shell->clen)
    {
        t_cmd *cmd = &shell->cmd[i];
        if (i < shell->clen - 1 && pipe(cmd->fd_pipe) == -1)
        {
            perror("pipe");
            g_exit_status = 1;
            exit(EXIT_FAILURE);
        }
        fork_and_execute(shell, cmd, prev_fd, i == shell->clen - 1);
        if (prev_fd != -1)
            close(prev_fd);
        if (i < shell->clen - 1)
        {
            close(cmd->fd_pipe[1]);
            prev_fd = cmd->fd_pipe[0];
        }
        i++;
    }
    while (waitpid(-1, &status, 0) > 0)
        update_exit_status(status);

}
