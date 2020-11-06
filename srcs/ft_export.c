/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:10:07 by grigo             #+#    #+#             */
/*   Updated: 2020/11/06 19:11:34 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check_ex_err(char **cmd, int i, int j)
{
	while (cmd[i][j])
	{
		if (cmd[i][j] == '+' && cmd[i][j + 1] == '=' && j != 0)
			return (0);
		if ((!ft_isalnum(cmd[i][j]) && cmd[i][j] != '=' && cmd[i][j] != '_')
		|| cmd[i][0] == '=' || (ft_isdigit(cmd[i][j]) && j == 0))
		{
			ft_puterror("bash: export: `", cmd[i],
				"': not a valid identifier\n", 1);
			return (-1);
		}
		if (cmd[i][j] == '=')
			return (0);
		j++;
	}
	return (-1);
}

char	**ft_modif_env_export(char **cmd, char **env, int i, int j)
{
	int		len;

	while (cmd[i][j] != '=' && cmd[i][j])
		j++;
	len = j;
	j = 0;
	while (env[j])
	{
		if (ft_strncmp(cmd[i], env[j], len) == 0)
		{
			free(env[j]);
			if (!(env[j] = (char *)malloc(sizeof(char) *
							(ft_strlen(cmd[i]) + 1))))
				return (NULL);
			ft_strcpy(env[j], cmd[i]);
			break ;
		}
		j++;
	}
	return (env);
}

char	**ft_get_ex_tmp(char *cmd, char **env, int j)
{
	char	**tmp;

	if (!(tmp = (char **)malloc(sizeof(char *) * (tab_len(env) + 2))))
		return (NULL);
	while (j < tab_len(env) - 1)
	{
		if (!(tmp[j] = (char *)malloc(sizeof(char) * (ft_strlen(env[j]) + 1))))
			return (NULL);
		ft_strcpy(tmp[j], env[j]);
		j++;
	}
	if (!(tmp[j] = (char *)malloc(sizeof(char) * (ft_strlen(cmd) + 1))))
		return (NULL);
	ft_strcpy(tmp[j], cmd);
	if (!(tmp[j + 1] = (char *)malloc(sizeof(char) * (ft_strlen(env[j]) + 1))))
		return (NULL);
	ft_strcpy(tmp[j + 1], env[j]);
	tmp[j + 2] = NULL;
	return (tmp);
}

char	**ft_get_ex_env(char **env, char **tmp, int j)
{
	ft_splitdel(&env);
	if (!(env = (char **)malloc(sizeof(char *) * (tab_len(tmp) + 1))))
		return (NULL);
	while (tmp[j])
	{
		if (!(env[j] = (char *)malloc(sizeof(char) * (ft_strlen(tmp[j]) + 1))))
			return (NULL);
		ft_strcpy(env[j], tmp[j]);
		j++;
	}
	env[j] = NULL;
	ft_splitdel(&tmp);
	tmp = NULL;
	return (env);
}

char	**ft_export(char **cmd, char **env)
{
	int		i;
	char	**tmp;

	tmp = NULL;
	i = 0;
	errno = 0;
	if (cmd[0] == NULL)
		return(sort_export(env));
	while (cmd[i])
	{
		if (ft_check_ex_err(cmd, i, 0) != -1)
		{
			if (ft_strchr(cmd[i], '=') != 0 && ft_checkex2(cmd[i], env) &&
					!ft_strchr(cmd[i], '+'))
			{
				tmp = ft_get_ex_tmp(cmd[i], env, 0);
				env = ft_get_ex_env(env, tmp, 0);
			}
			else if (ft_strchr(cmd[i], '=') && ft_strchr(cmd[i], '+'))
				env = ft_add_env_export(cmd[i], env, NULL, 0);
			if (!ft_checkex2(cmd[i], env))
				env = ft_modif_env_export(cmd, env, i, 0);
		}
		i++;
	}
	return (env);
}
