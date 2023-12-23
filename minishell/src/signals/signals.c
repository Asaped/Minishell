/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 18:51:11 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/23 13:35:13 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	reset_signal(int signal_nb)
{
	(void)signal_nb;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	skip_sigquit(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	signals_on(void)
{
	struct sigaction	sa;

	skip_sigquit();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &reset_signal;
	sigaction(SIGINT, &sa, NULL);
}

void	signal_print_nl(int sig)
{
	(void)sig;
	rl_on_new_line();
}

void	signals_off(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &signal_print_nl;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
