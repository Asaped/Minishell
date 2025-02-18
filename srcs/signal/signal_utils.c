/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: nigateau <nigateau@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/01/20 20:28:53 by nigateau          #+#    #+#             */
/*   Updated: 2025/01/20 20:28:53 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	handle_interactive(int sig)
{
	g_exit_status = sig + 128;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_interactive_heredoc(int sig)
{
	g_exit_status = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_done = 1;
	rl_on_new_line();
}

void	handle_non_interactive(int sig)
{
	g_exit_status = sig + 128;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}
