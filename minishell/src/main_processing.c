/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:25:01 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/15 18:26:46 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	processing(t_data *data)
{
	// Etape 1: Tokenisation
	if (!init_tokens(data))
		return (error_back("Check syntax."));
	// Etape 2: Construction de AST
	// Etape 3: Check syntax
	// Etape 4: Execution
	// Etape 5: Post-traitement
}
