/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:51:36 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/14 19:19:53 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*str)
	{
		if (*str != c && count == 0)
		{
			count = 1;
			i++;
		}
		else if (*str == c)
			count = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc(sizeof(char) * (finish - start + 1));
	if (!word)
		return (NULL);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static void	*ft_free(char **strs, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		free(strs[i++]);
	free(strs);
	return (NULL);
}

char	**ft_split(char *s, char c)
{
	size_t	i;
	size_t	k;
	int		index;
	char	**result;

	i = -1;
	k = 0;
	index = -1;
	result = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !result)
		return (NULL);
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			result[k] = word_dup(s, index, i);
			if (!result[k++])
				return (ft_free(result, k));
			index = -1;
		}
	}
	result[k] = 0;
	return (result);
}
