/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:49:16 by nigateau          #+#    #+#             */
/*   Updated: 2025/01/20 20:49:16 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	print_cmd(t_mini *shell)
{
	int	i;
	int	j;

	i = -1;
	while (++i < shell->clen)
	{
		j = -1;
		printf("-----command[%d]-----\n", i);
		printf("token len = %d\n", shell->cmd[i].tlen);
		printf("path_bin = \"%s\"\n", shell->cmd[i].path_bin);
		while (++j < shell->cmd[i].tlen)
			printf("token[%d] = \"%s\"\n", j, shell->cmd[i].token[j]);
		printf("heredoc_key = \"%s\"\n", shell->cmd[i].heredoc_key);
		printf("input = \"%s\"\n", shell->cmd[i].input);
		printf("output = \"%s\"\n", shell->cmd[i].output);
		printf("fd_in value = %d\n", shell->cmd[i].fd_in);
		printf("fd_out value = %d\n", shell->cmd[i].fd_out);
		printf("-----command[%d]-----\n\n", i);
	}
}

void	print_token(t_mini *shell)
{
	int	i;

	i = -1;
	printf("\n");
	printf("INPUT = \"%s\"\n", shell->input);
	printf("\n");
	printf("PATH = \"%s\"\n", shell->path);
	printf("\n");
	printf("-----token-----\n");
	printf("\n");
	while (++i < shell->tlen)
	{
		if (shell->token[i].type == BUILTIN)
			printf("TYPE = BUILTIN\n");
		else if (shell->token[i].type == CMD)
			printf("TYPE = CMD\n");
		else if (shell->token[i].type == STRING)
			printf("TYPE = STRING\n");
		else if (shell->token[i].type == OPERATOR)
			printf("TYPE = OPERATOR\n");
		else if (shell->token[i].type == UNKNOWN)
			printf("TYPE = UNKNOWN\n");
		if (shell->token[i].path_bin != NULL)
			printf("PATH_BIN = \"%s\"\n", shell->token[i].path_bin);
		printf("VALUE = \"%s\"\n", shell->token[i].value);
		printf("LEN = %d\n\n", shell->token[i].len);
	}
	printf("-----token-----\n");
}

void	print_env(char **env)
{
	int	i;

	i = -1;
	while (++i < ft_tablen(env))
		printf("env[%d] = \'%s\'\n", i, env[i]);
}
