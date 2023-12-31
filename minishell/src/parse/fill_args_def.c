/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args_def.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:58:07 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:30:52 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Compte le nombre d'arguments de la commande
static int	count_arguments(t_token *temp)
{
	int	i;

	i = 0;
	while (temp && (temp->type == WORD || temp->type == VAR))
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

// Crée la liste d'arguments par défaut pour une commande.
// Inclut le nom de la commande suivi de ses arguments.
int	create_args_def(t_token **token_node, t_cmd *last_cmd)
{
	int		i;
	int		nb_args;
	t_token	*temp;

	i = 0;
	temp = *token_node;
	nb_args = count_arguments(temp);
	last_cmd->args = malloc(sizeof(char *) * (nb_args + 2));
	if (!last_cmd->args)
		return (FAILURE);
	temp = *token_node;
	i = 0;
	last_cmd->args[i] = ft_strdup(last_cmd->command);
	i++;
	while (temp->type == WORD || temp->type == VAR)
	{
		last_cmd->args[i] = ft_strdup(temp->str);
		i++;
		temp = temp->next;
	}
	last_cmd->args[i] = NULL;
	*token_node = temp;
	return (SUCCESS);
}

// Copie les arguments existants dans un nouveau tableau
// Ajoute les nouveaux arguments
static char	**copy_def_tab(int len, char **tab, t_cmd *last_cmd, t_token **tks)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = *tks;
	while (i < len)
	{
		tab[i] = last_cmd->args[i];
		i++;
	}
	while (temp->type == WORD || temp->type == VAR)
	{
		tab[i] = ft_strdup(temp->str);
		i++;
		temp = temp->next;
	}
	tab[i] = NULL;
	return (tab);
}

// Ajoute des arguments supplémentaires à une commande déjà initialisée
int	add_args_def(t_token **token_node, t_cmd *last_cmd)
{
	int		i;
	int		len;
	char	**new_tab;
	t_token	*temp;

	i = 0;
	temp = *token_node;
	while (temp->type == WORD || temp->type == VAR)
	{
		i++;
		temp = temp->next;
	}
	len = 0;
	while (last_cmd->args[len])
		len++;
	new_tab = malloc(sizeof(char *) * (i + len + 1));
	if (!new_tab)
		return (FAILURE);
	new_tab = copy_def_tab(len, new_tab, last_cmd, token_node);
	free(last_cmd->args);
	last_cmd->args = new_tab;
	*token_node = temp;
	return (SUCCESS);
}

// Remplit les arguments d'une commande en fonction de son type
// Traite spécialement la commande 'echo'
int	fill_args(t_token **token_node, t_cmd *last_cmd)
{
	if (!ft_strcmp(last_cmd->command, "echo"))
	{
		if (!(last_cmd->args))
			return (create_args_echo(token_node, last_cmd));
		else
			return (add_args_echo(token_node, last_cmd));
	}
	else
	{
		if (last_cmd && !(last_cmd->args))
			return (create_args_def(token_node, last_cmd));
		else
			return (add_args_def(token_node, last_cmd));
	}
	return (SUCCESS);
}
