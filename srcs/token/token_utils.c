#include "../../incs/minishell.h"

int	wordlen(const char *s, int i)
{
	int	j;

	j = 0;
	if (is_op(s[i]) && !is_op(s[i + 1]))
		return (1);
	else if (is_op(s[i]) && is_op(s[i + 1]))
		return (2);
	else if (is_quote(s[i]))
		return (skip_quote(s, i));
	while (s[i + j] && !is_whitespace(s[i + j]) && !is_op(s[i + j]) && !is_quote(s[i + j]))
		j++;
	return (j);
}

char	*worddup(const char *s, int i, int *n)
{
	int		j;
	char	*str;

	j = 0;
	if (is_quote(s[i]))
	{
		i++;
		n[0] -= 2;
	}
	str = malloc(sizeof(char) * (n[0] + 1));
	if (!str)
		return (NULL);
	while (j < n[0])
	{
		str[j] = s[i + j];
		j++;
	}
	str[j] = 0;
	return (str);
}

int	skip_quote(const char *str, int i)
{
	int	j;

	j = 1;
	while (str[i + j] && str[i + j] != str[i])
		j++;
	if (str[i + j] == str[i])
		j++;
	return (j);
}