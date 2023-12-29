/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:45:17 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:11:57 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Vérifie si l'input contient uniquement des espaces
static bool	input_is_space(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (!ft_isspace(input[i]))
			return (false);
	}
	return (true);
}

// Analyse l'input et prépare le traitement des commandes
// Gère les cas d'entrée vide
// Ajoute l'input à l'historique des commandes
// Passe l'input à la fonction de tokenisation pour créer une liste de tokens
// Vérifie et traite les variables dans les tokens
// Gère les guillemets dans les tokens
// Crée des structures de commande basées sur les tokens
bool	parse_user_input(t_data *data)
{
	if (data->user_input == NULL)
		builtin_exit(data, NULL);
	else if (ft_strcmp(data->user_input, "\0") == SUCCESS)
		return (false);
	else if (input_is_space(data->user_input))
		return (true);
	add_history(data->user_input);
	if (tokenization(data, data->user_input) == FAILURE)
		return (false);
	if (data->token->type == END)
		return (false);
	if (check_if_var(&data->token) == FAILURE)
		return (false);
	var_expander(data, &data->token);
	quotes_handler(data);
	create_commands(data, data->token);
	return (true);
}
