/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 13:01:17 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:59:22 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Analyse token PIPE, prépare commande pour piping. Définit `pipe_output`
// Ajoute commande pour côté droit du pipe. Avance le token après PIPE
void	parse_pipe(t_cmd **cmd, t_token **token_lst)
{
	t_cmd	*last;

	last = last_cmd(*cmd);
	last->pipe_output = true;
	cmd_adder(&last, cmd_creator(false));
	*token_lst = (*token_lst)->next;
}
