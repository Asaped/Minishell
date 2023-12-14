/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:22:10 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/14 20:48:44 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* -------------------------------------------------------------------------- */
/* Permet d'allouer de la memoire avec malloc en une ligne dans le programme  */
/* -------------------------------------------------------------------------- */
void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
		error_exit("Malloc error.");
	return (ret);
}
