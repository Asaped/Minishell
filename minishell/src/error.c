/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:42:11 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/15 17:31:07 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	error_back(const char *err_msg)
{
	printf(R "Error: " RST);
	printf("%s\n", err_msg);
}

void	error_exit(const char *err_msg)
{
	printf(R "Error: " RST);
	printf("%s\n", err_msg);
	exit(1);
}
