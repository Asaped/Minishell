/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:47:28 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 20:02:36 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parse_pipe(t_cmd **cmds, t_token **tokens)
{
	t_cmd	*cmd;

	cmd = last_cmd(*cmds);
	cmd->pipe_output = true;
	add_cmd(&cmd, create_cmd(false));
	*tokens = (*tokens)->next;
}
