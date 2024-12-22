/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.lausanne>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:57:37 by nigateau          #+#    #+#             */
/*   Updated: 2024/12/20 16:51:01 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int exec_builtin(t_cmd *cmd, t_mini *shell)
{
    if (!ft_strncmp(cmd->token[0], "echo", ft_strlen("echo")))
        return ft_echo(cmd->token);
    if (!ft_strncmp(cmd->token[0], "cd", ft_strlen("cd")))
        return ft_cd(shell, cmd->token);
    if (!ft_strncmp(cmd->token[0], "pwd", ft_strlen("pwd")))
        return ft_pwd();
    if (!ft_strncmp(cmd->token[0], "export", ft_strlen("export")))
        return ft_export(shell, cmd->token);
    if (!ft_strncmp(cmd->token[0], "unset", ft_strlen("unset")))
        return ft_unset(shell->env, cmd->token);
    if (!ft_strncmp(cmd->token[0], "env", ft_strlen("env")))
        return ft_env(shell->env, cmd->token, 0);
    if (!ft_strncmp(cmd->token[0], "exit", ft_strlen("exit")))
        return ft_exit(shell, *cmd);
    return 0;
}

// Récupère le status de retour
void update_exit_status(int status)
{
    if (WIFEXITED(status))
        g_exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        g_exit_status = 128 + WTERMSIG(status);
}

