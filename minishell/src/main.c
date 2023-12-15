/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:02:23 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/15 17:31:09 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	t_data	data;

	init_data(&data);
	// TODO : gestion des signaux !
	while (1)
	{
		data.input = readline(data.prompt_msg);
		if (data.input == NULL)
		{
			printf("\nGood bye !\n");
			break ;
		}
		if (*data.input)
			processing(&data); // fonction pour gerer parsing, tokenisation et exec 
		free(data.input);
	}
	// Nettoyage et sortie
	// Libérez toutes les ressources allouées
	return (0);
}
