/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigateau <nigateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:03:47 by nigateau          #+#    #+#             */
/*   Updated: 2025/01/20 21:03:49 by nigateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool	is_valid_key(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i++] != '_')
		return (FALSE);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (FALSE);
		i++;
	}
	if (str[i] != '=')
		return (FALSE);
	return (TRUE);
}

int	get_env_index(char **env, char *key)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, key_len) && (env[i][key_len] == '='
			|| !env[i][key_len]))
			return (i);
		i++;
	}
	return (-1);
}

char	**realloc_env(char **env, int len)
{
	int		i;
	char	**res;

	i = -1;
	res = malloc(sizeof(char *) * (len + 1));
	res[len] = NULL;
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
	int		i;
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

char	**get_key_and_value(char *str)
{
	char	*pos;
	char	**tmp;

	tmp = malloc(sizeof(char *) * 3);
	if (!tmp)
		return (NULL);
	if ((pos = ft_strchr(str, '=')) == NULL)
	{
		tmp[0] = ft_strdup(str);
		tmp[1] = NULL;
		return (tmp);
	}
	tmp[0] = ft_substr(str, 0, pos - str);
	tmp[1] = ft_substr(pos, 1, ft_strlen(pos));
	tmp[2] = NULL;
	return (tmp);
}

t_bool	ft_export(t_mini *shell, t_cmd *cmd)
{
	int		i;
	char	**tmp;

	if (cmd->tlen == 1)
	{
		return (ft_env(shell->env, cmd, 1));
	}
	i = 0;
	while (++i < cmd->tlen)
	{
		if (!is_valid_key(cmd->token[i]))
			return (fprintf(stderr,
					"bash: export: `%s': not a valid identifier\n",
					cmd->token[i]), TRUE);
		if (cmd->token[i])
		{
			tmp = get_key_and_value(cmd->token[i]);
			shell->env = set_env_var(shell->env, tmp[0], tmp[1]);
			free_tab(tmp);
		}
	}
	return (FALSE);
}
