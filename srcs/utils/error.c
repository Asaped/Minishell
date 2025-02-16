/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.lausanne>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:16:27 by nigateau          #+#    #+#             */
/*   Updated: 2025/02/16 17:47:45 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	f_printf(int std, char *s1, char *s2, char *s3)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		write(std, &s1[i], 1);
		i++;
	}
	i = 0;
	while(s2[i])
	{
		write(std, &s2[i], 1);
		i++;
	}
	i = 0;
	while (s3[i])
	{
		write(std, &s3[i], 1);
		i++;
	}
	write(std, "\n", 1);
	return ;
}
