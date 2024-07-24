#include "../../incs/minishell.h"

int	wordlen(const char *s, int i)
{
	int	j;

	j = 0;
	if (is_op(s[i]))
	{
		if (!is_op(s[i + 1]))
			return (1);
		return (2);
	}
	else if (is_quote(s[i]))
		return (j += skip_quote(s, i));
	else if (s[i] == '$')
		j++;
	while (s[i + j] && s[i + j] != ' ' && s[i + j] != '$' && !is_quote(s[i + j]) && !is_op(s[i + j]))
		j++;
	return (j);
}

char	*worddup(const char *s, int i, int n)
{
	int		j;
	char	*str;

	j = 0;
	str = malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	while (j < n)
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
	while (str[i + j] && str[i + j] != '\'' && str[i + j] != '\"')
		j++;
	if (str[i + j] == '\'' || str[i + j] == '\"')
		j++;
	return (j);
}