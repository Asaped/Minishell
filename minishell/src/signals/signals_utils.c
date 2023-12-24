/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 10:25:03 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/24 10:26:27 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	nothing(int v)
{
	(void)v;
	ft_putstr_fd("Quit: 3\n", 1);
	rl_redisplay();
}

void	backslash_n(int v)
{
	(void)v;
	write(1, "\n", 1);
	rl_redisplay();
}

void	sigquit_update(void)
{
	struct sigaction	action;

	action.sa_handler = &nothing;
	sigaction(SIGQUIT, &action, NULL);
}

void	sigint_update(void)
{
	struct sigaction	action;

	action.sa_handler = &backslash_n;
	sigaction(SIGINT, &action, NULL);
}
