#include "../../incs/minishell.h"

static char	**remove_env(char **env, int pos)
{
    int     len;
    char    *tmp;

    len = ft_tablen(env);

    while (pos < len - 1)
    {
        tmp = env[pos];
        env[pos] = env[pos + 1];
        env[++pos] = tmp;
    }
    free(env[pos]);
	env[pos] = NULL;
    env = realloc_env(env, len - 1);
    return (env);
}

t_bool	ft_unset(char **env, char **token)
{
    int i;
    int pos;

    i = 0;
    while (token[++i])
    {
    	pos = get_env_index(env, token[i]);
		if (pos != -1)
		{
    		env = remove_env(env, pos);
			return (TRUE);
		}
    }
    return (FALSE);
}