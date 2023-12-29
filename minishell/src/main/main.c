/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:48:02 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:25:58 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Boucle principale du shell
// Affiche le prompt, lit la saisie de l'utilisateur, et exécute les commandes
// Gère les signaux et nettoie les données après chaque commande
static void	minishell(t_data *data)
{
	char	*prompt;

	while (1)
	{
		signals_on();
		prompt = get_prompt(data);
		printf("%s\n", prompt);
		data->user_input = readline(Y "$> " RST);
		signals_off();
		if (parse_user_input(data) == true)
			g_exit_status = execute(data);
		else
			g_exit_status = FAILURE;
		free_ptr(prompt);
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
	minishell(&data);
	exit_shell(&data, g_exit_status);
	return (SUCCESS);
}
