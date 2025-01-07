/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.lausanne>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:45:17 by nigateau          #+#    #+#             */
/*   Updated: 2025/01/07 18:55:31 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

// Gestion des pipes pour une commande donnée
void setup_pipes(t_cmd *cmd, int prev_fd, int is_last_cmd)
{
    if (prev_fd != -1)
    {
        if (dup2(prev_fd, STDIN_FILENO) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(prev_fd);
    }
    if (!is_last_cmd)
    {
        if (dup2(cmd->fd_pipe[1], STDOUT_FILENO) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(cmd->fd_pipe[1]);
    }
    close(cmd->fd_pipe[0]);
}

void setup_redirections(t_cmd *cmd)
{
    if (cmd->input)
    {
        if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(cmd->fd_in);
    }
    
    if (cmd->output)
    {
        if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(cmd->fd_out);
    }
}

// Exécution d'une commande
void execute_command(t_cmd *cmd, char **env)
{
    check_dot_and_file(cmd);

    if (access(cmd->path_bin, F_OK) == -1)
    {
        fprintf(stderr, "%s: Command not found\n", cmd->token[0]);
        g_exit_status = 127; // Commande introuvable
        return;
    }

    if (access(cmd->path_bin, X_OK) == -1)
    {
        fprintf(stderr, "%s: Permission denied\n", cmd->token[0]);
        g_exit_status = 126; // Commande non exécutable
        return;
    }

    if (execve(cmd->path_bin, cmd->token, env) == -1)
    {
        perror(cmd->token[0]); // Affiche une erreur détaillée
        g_exit_status = 127;  // Commande introuvable
        exit(127);
    }
}

void    check_dot_and_file(t_cmd *cmd)
{
    struct stat sb;

    if (!cmd || !cmd->token[0])
    {
        g_exit_status = 0; // Rien à exécuter, succès
        return;
    }

    if (strcmp(cmd->token[0], ".") == 0 && (!cmd->token[1] || cmd->token[1][0] == '\0'))
    {
        fprintf(stderr, ".: filename argument required\n");
        g_exit_status = 2; // Usage incorrect
        return;
    }

    if (stat(cmd->token[0], &sb) == 0)
    {
        if (S_ISDIR(sb.st_mode))
        {
            fprintf(stderr, "%s: is a directory\n", cmd->token[0]);
            g_exit_status = 126; // Commande non exécutable
            return;
        }
    }
    return;
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
        //signal(SIGINT, SIG_DFL);  // Rétablit le comportement par défaut pour l'enfant
        //signal(SIGQUIT, SIG_DFL); // Rétablit également SIGQUIT si nécessaire
        setup_pipes(cmd, prev_fd, is_last_cmd);
        setup_redirections(cmd);
        execute_command(cmd, shell->env);
    }
    else // Processus parent
    {
        //signal(SIGINT, SIG_IGN);  // Ignore SIGINT pendant que l'enfant s'exécute
        //signal(SIGQUIT, SIG_IGN);
        if (prev_fd != -1)
            close(prev_fd);
        if (!is_last_cmd)
            close(cmd->fd_pipe[1]);
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

        if (is_builtin(cmd->token[0]))
        {
            execute_builtin(cmd, shell, &prev_fd, i);
            i++;
            continue;
        }
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

