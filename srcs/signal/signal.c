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

static void	handle_interactive(int sig)
{
	g_exit_status = sig + 128;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_interactive_heredoc(int sig)
{
	g_exit_status = sig;
	rl_replace_line("", 0);
	rl_on_new_line();
}

static void	handle_non_interactive(int sig)
{
	g_exit_status = sig + 128;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
}

void	signal_handler_interactive(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &handle_interactive;
	sigaction(SIGINT, &act, NULL);
}

void	signal_handler_interactive_heredoc(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &handle_interactive_heredoc;
	sigaction(SIGINT, &act, NULL);
}

void	signal_handler_non_interactive(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &handle_non_interactive;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
