/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moturki <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:10:38 by moturki           #+#    #+#             */
/*   Updated: 2023/10/23 11:10:39 by moturki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_word(char const *s, char c, size_t i, size_t count)
{
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

size_t	word_length(char const *s, char c, size_t i)
{
	while (s[i] != c && s[i])
		i++;
	return (i);
}

char	*set_word(char const *s, char c, size_t i, size_t j)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (word_length(s, c, 0) + 1));
	if (!str)
		return (NULL);
	while (s[j] != c && s[j])
		str[i++] = s[j++];
	str[i] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	count;

	if (!s)
		return (NULL);
	count = count_word(s, c, 0, 0);
	tab = (char **)malloc((count + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		tab[i++] = set_word(s, c, 0, 0);
		while (*s != c && *s)
			s++;
	}
	tab[count] = 0;
	return (tab);
}
