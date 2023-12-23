/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 11:50:07 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/22 20:48:40 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	main_minishell(t_data *data)
{
	while (1)
	{
		signals_on();
		data->user_input = readline(PROMPT);
		signals_off();
		if (parser(data) == TRUE)
			g_exit_status = execution(data);
		else
			g_exit_status = 1;
		free_data(data, false);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	ft_memset(&data, 0, sizeof(t_data));
	if (!init_data(&data, env))
		exit_shell(NULL, EXIT_FAILURE);
	main_minishell(&data);
	exit_shell(&data, g_exit_status);
	return (0);
}
