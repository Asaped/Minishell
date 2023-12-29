/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:47:03 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/29 13:20:23 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Enregistre un token de séparateur dans la liste des tokens.
// Gère les séparateurs spéciaux (comme '>>' et '<<') et les sép standards.
// Utilisé pour traiter les redirections et les opérateurs
int	save_separator(t_token **token_lst, char *str, int index, int type)
{
	int		i;
	char	*sep;

	i = 0;
	if (type == APPEND || type == HEREDOC)
	{
		sep = malloc(sizeof(char) * 3);
		if (!sep)
			return (1);
		while (i < 2)
			sep[i++] = str[index++];
		sep[i] = '\0';
		add_token(token_lst, create_token(sep, NULL, type, DEFAULT));
	}
	else
	{
		sep = malloc(sizeof(char) * 2);
		if (!sep)
			return (1);
		while (i < 1)
			sep[i++] = str[index++];
		sep[i] = '\0';
		add_token(token_lst, create_token(sep, NULL, type, DEFAULT));
	}
	return (0);
}

// Enregistre un token de mot dans la liste des tokens
// Extrait un mot de la chaîne de commande et crée un token de type 'WORD'
// Utilisé pour traiter les commandes et les arguments
int	save_word(t_token **token_lst, char *str, int index, int start)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (index - start + 1));
	if (!word)
		return (1);
	while (start < index)
	{
		word[i] = str[start];
		start++;
		i++;
	}
	word[i] = '\0';
	add_token(token_lst, \
			create_token(word, ft_strdup(word), WORD, DEFAULT));
	return (0);
}

// Identifie si un caractère est un séparateur
// Détermine le type de séparateur (espace, pipe, redirection, etc.)
// Utilisé pour identifier les elements entrés
int	is_separator(char *str, int i)
{
	if (((str[i] > 8 && str[i] < 14) || str[i] == 32))
		return (SPACES);
	else if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	else if (str[i] == '<')
		return (INPUT);
	else if (str[i] == '>')
		return (TRUNC);
	else if (str[i] == '\0')
		return (END);
	else
		return (0);
}

// Met à jour l'état de quotation pour un token
// Gère l'entrée et la sortie des états de quote simples et doubles
// Utilisé pour traiter correctement les chaînes entre quotes
int	set_status(int status, char *str, int i)
{
	if (str[i] == '\'' && status == DEFAULT)
		status = SQ;
	else if (str[i] == '\"' && status == DEFAULT)
		status = DQ;
	else if (str[i] == '\'' && status == SQ)
		status = DEFAULT;
	else if (str[i] == '\"' && status == DQ)
		status = DEFAULT;
	return (status);
}

// Décide si un caractère fait partie d'un mot ou d'un séparateur
// Utilisé pour décomposer la commande de l'utilisateur en tokens
int	save_word_or_sep(int *i, char *str, int start, t_data *data)
{
	int	type;

	type = is_separator(str, (*i));
	if (type)
	{
		if ((*i) != 0 && is_separator(str, (*i) - 1) == 0)
			save_word(&data->token, str, (*i), start);
		if (type == APPEND || type == HEREDOC || type == PIPE
			|| type == INPUT || type == TRUNC || type == END)
		{
			save_separator(&data->token, str, (*i), type);
			if (type == APPEND || type == HEREDOC)
				(*i)++;
		}
		start = (*i) + 1;
	}
	return (start);
}
