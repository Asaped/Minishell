/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 11:52:42 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/16 19:25:12 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*

	- remove_comments()
		supprime tout le reste de la chaine apres avoir trouve un
		commentaire commencat par # (comportement de base du shell),
		sauf si celui ci est entre quotes

	- quotes_order()
		verifie si toutes les quotes sont ouvertes et fermees dans
		le bon ordre (ordre canonique).
	
	- quotes_count()
		verifie si le nombre de quotes est correct, donc si il
		n'y a pas de quotes qui ne sont pas restees ouvertes
	
	- remove_escape_sequences()
		supprime tout les espaces inutiles qui ne se trouvent 
		pas entre quotes

	- format_and_checks()
		orchestre l'appel de toutes ces fonctions dans
		l'ordre, et retourne : (0) si erreur ou (1) si tout est OK

*/

static int	remove_comments(char **input, t_tools tools)
{
	char	*output;
	int		i;

	output = safe_malloc(ft_strlen(*input) + 1);
	if (!output)
		return (0);
	i = 0;
	while ((*input)[i])
	{
		if (ft_isquote((*input)[i]))
			tools.in_quote = !tools.in_quote;
		else if ((*input)[i] == '#' && !tools.in_quote)
			break ;
		output[tools.len++] = (*input)[i++];
	}
	output[tools.len] = '\0';
	free(*input);
	*input = output;
	if (!ft_strlen(*input))
		return (0);
	return (1);
}

static int	quotes_order(char *input, char s_quote, char d_quote)
{
	int	in_s_quote;
	int	in_d_quote;
	int	i;

	in_s_quote = 0;
	in_d_quote = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == s_quote)
		{
			if (in_d_quote == 0)
				in_s_quote = !in_s_quote;
		}
		else if (input[i] == d_quote)
		{
			if (in_s_quote == 0)
				in_d_quote = !in_d_quote;
		}
	}
	if (in_s_quote || in_d_quote)
		return (0);
	return (1);
}

static int	quotes_count(char *input, char s_quote, char d_quote)
{
	int	count_s_quote;
	int	count_d_quote;
	int	i;

	count_d_quote = 0;
	count_s_quote = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == s_quote)
			count_s_quote++;
		else if (input[i] == d_quote)
			count_d_quote++;
	}
	if (count_s_quote % 2 != 0 || count_d_quote % 2 != 0)
		return (0);
	return (1);
}

static int	remove_escape_sequences(char **input, t_tools tools)
{
	char	*output;
	int		i;

	output = safe_malloc(ft_strlen(*input) + 1);
	i = 0;
	while ((*input)[i])
	{
		if (ft_isquote((*input)[i]))
			tools.in_quote = !tools.in_quote;
		else if (!ft_isescape((*input)[i]) || tools.in_quote)
			output[tools.len++] = (*input)[i];
		i++;
	}
	output[tools.len] = '\0';
	free(*input);
	*input = output;
	if (!ft_strlen(*input))
		return (0);
	return (1);
}

int	formats_and_checks(t_data *data)
{
	t_tools	tools;

	tools.in_quote = false;
	tools.len = 0;
	if (!data->input)
		return (0);
	if (!remove_comments(&(data->input), tools))
		return (0);
	if (!quotes_count(data->input, '\'', '\"')
		|| !quotes_order(data->input, '\'', '\"'))
		return (0);
	if (!remove_escape_sequences(&(data->input), tools))
		return (0);
	return (1);
}
