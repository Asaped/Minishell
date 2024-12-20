#include "../../incs/minishell.h"

t_bool is_valid_key(char *str)
{
    int i;

    i = 0;
    if (!ft_isalpha(str[i]) && str[i++] != '_')
        return (FALSE);
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (FALSE);
        i++;
    }
    return (TRUE);
}

int get_env_index(char **env, char *key)
{
    int i;
    int key_len;

    i = 0;
    key_len = ft_strlen(key);
    while (env[i])
    {
        if (!ft_strncmp(env[i], key, key_len) && (env[i][key_len] == '=' || !env[i][key_len]))
            return (i);
        i++;
    }
    return (-1);
}

char    **realloc_env(char **env, int len)
{
    int     i;
    char    **res;

    i = -1;
    res = malloc(sizeof(char *) * (len + 1));
	env[len] = NULL;
    if (!res)
        return (NULL);
    while (env[++i] && i < len)
    {
        res[i] = ft_strdup(env[i]);
        free(env[i]);
    }
    free(env);
    return (res);
}

char	**set_env_var(char **env, char *key, char *value)
{
    int     i;
	char	*new_value;

    i = 0;
    i = get_env_index(env, key);
    if (!value)
		value = "";
	new_value = ft_strjoin3("=", value);
    if (i != -1 && env[i])
    {
        free(env[i]);
        env[i] = ft_strjoin3(key, new_value);
    }
    else
    {
        i = ft_tablen(env);
        env = realloc_env(env, i + 1);
        if (!env)
            return (NULL);
		env[i] = ft_strjoin3(key, new_value);
    }
    return (env);
}

static char **get_key_and_value(char *str)
{
    char    *pos;
    char    **tmp;

    tmp = malloc(sizeof(char *) * 3);
    if (!tmp)
        return (NULL);
    pos = ft_strchr(str, '=');
    tmp[0] = ft_substr(str, 0, pos - str);
    tmp[1] = ft_substr(pos, 1, ft_strlen(pos));
    tmp[2] = NULL;
    return (tmp);
}

t_bool ft_export(t_mini *shell, char **token)
{
    int		i;
    char    **tmp;

    if (!token[1])
	{
        return (ft_env(shell->env, NULL, 1));
	}
	i = 0;
	while (token[++i])
    {
        if (!is_valid_key(token[i]))
            return (ft_error("export: "), ft_error("`"), ft_error(token[i]), ft_error("\'"), ft_error(": not a valid identifier\n"));
        else
        {
            tmp = get_key_and_value(token[i]);
            shell->env = set_env_var(shell->env, tmp[0], tmp[1]);
            free_tab(tmp);
        }
    }
    return (TRUE);
}