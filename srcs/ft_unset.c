/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:04:24 by grigo             #+#    #+#             */
/*   Updated: 2020/10/29 13:50:01 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check_unset_err(char **cmd, int i, int j)
{
	while (cmd[i][j])
	{
		if (!ft_isalnum(cmd[i][j]) && cmd[i][j] != '_')
		{
			ft_puterror("bash: unset: `", cmd[i],
				"': not a valid identifier\n", 1);
			return (-1);
		}
		j++;
	}
	return (0);
}

char	*ft_creat_unset_tcmd(char **cmd, int i, int j)
{
	char	*tcmd;

	if (!(tcmd = (char *)malloc(sizeof(char) * (ft_strlen(cmd[i]) + 2))))
		return (NULL);
	j = 0;
	while (cmd[i][j])
	{
		tcmd[j] = cmd[i][j];
		j++;
	}
	tcmd[j] = '=';
	tcmd[j + 1] = '\0';
	return (tcmd);
}

char	**ft_get_unset_tmp(char **env, int idx, int j)
{
	char	**tmp;

	if (!(tmp = (char **)malloc(sizeof(char *) * (tab_len(env)))))
		return (NULL);
	while (j < idx)
	{
		if (!(tmp[j] = (char *)malloc(sizeof(char) * (ft_strlen(env[j]) + 1))))
			return (NULL);
		ft_strcpy(tmp[j], env[j]);
		j++;
	}
	j++;
	while (j < tab_len(env))
	{
		if (!(tmp[j - 1] = (char *)malloc(sizeof(char) *
					(ft_strlen(env[j]) + 1))))
			return (NULL);
		ft_strcpy(tmp[j - 1], env[j]);
		j++;
	}
	tmp[j - 1] = NULL;
	return (tmp);
}

char	**ft_get_unset_env(char **env, char **tmp, int j)
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

char	**ft_unset(char **cmd, char **env)
{
	int		i;
	int		idx;
	char	**tmp;
	char	*tcmd;

	tmp = NULL;
	i = 1;
	errno = 0;
	while (cmd[i])
	{
		if (ft_check_unset_err(cmd, i, 0) != -1)
		{
			tcmd = ft_creat_unset_tcmd(cmd, i, 0);
			if ((idx = ft_checkunset(tcmd, env) - 1) != -1)
			{
				tmp = ft_get_unset_tmp(env, idx, 0);
				env = ft_get_unset_env(env, tmp, 0);
			}
			free(tcmd);
		}
		i++;
	}
	return (env);
}
