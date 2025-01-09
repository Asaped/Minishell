/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.lausanne>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:16:27 by nigateau          #+#    #+#             */
/*   Updated: 2025/01/09 17:56:21 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void    f_printf(int std, char *error_msg, char *token)
{
    int i;

    i = 0;
    while (token[i])
    {
        write(std, &token[i], 1);
        i++;
    }
    write(std, " : ", 3);
    i = 0;
    while (error_msg[i])
    {
        write(std, &error_msg[i], 1);
        i++;
    }
    write(std, "\n", 1);
    return;
}
