#include "../../incs/minishell.h"

char	*expand_env(t_mini *shell, char *str)
{
	char	result[4096];
	char    *tmp;
	int		i;
    int     j;
    int     k;

    i = 0;
    j = 0;
	ft_bzero(result, 4096);
    while (str[i])
    {
        while (str[i] && str[i] != '$')
            result[j++] = str[i++];
        if (str[i] == '$' && str[i + 1] && str[i + 1] != '$' && !is_op(str[i + 1]) && !is_whitespace(str[i + 1]))
        {
            tmp = get_env_value(shell, worddup(str, ++i, wordlen2(str, &i)), 1);
            k = 0;
            while (tmp && tmp[k])
                result[j++] = tmp[k++];
        }
        else if (str[i] == '$' || (str[i] == '$' && str[i + 1] == '$'))
            result[j++] = str[i++];
    }
	free(str);
	return (ft_strdup(result));
}