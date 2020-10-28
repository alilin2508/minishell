/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:10:07 by grigo             #+#    #+#             */
/*   Updated: 2020/10/28 17:12:09 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_export(char **cmd, char **env)
{
	int		i;
	int		j;
	char	**tmp;
	int		len;

	tmp = NULL;
	i = 0;
	errno = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if ((!ft_isalnum(cmd[i][j]) && cmd[i][j] != '=' && cmd[i][j] != '_')
			|| cmd[i][0] == '=')
			{
				ft_puterror("bash: export: `", cmd[i],
					"': not a valid identifier\n", 1);
				j = -1;
				break ;
			}
			if (cmd[i][j] == '=')
				break ;
			j++;
		}
		if (j != -1)
		{
			if (strchr(cmd[i], '=') != 0 && ft_checkex2(cmd[i], env))
			{
				if (!(tmp = (char **)malloc(sizeof(char *) *
								(tab_len(env) + 2))))
					return (NULL);
				j = 0;
				while (j < tab_len(env) - 1)
				{
					if (!(tmp[j] = (char *)malloc(sizeof(char) *
								(ft_strlen(env[j]) + 1))))
						return (NULL);
					ft_strcpy(tmp[j], env[j]);
					j++;
				}
				if (!(tmp[j] = (char *)malloc(sizeof(char) *
								(ft_strlen(cmd[i]) + 1))))
					return (NULL);
				ft_strcpy(tmp[j], cmd[i]);
				if (!(tmp[j + 1] = (char *)malloc(sizeof(char) *
								(ft_strlen(env[j]) + 1))))
					return (NULL);
				ft_strcpy(tmp[j + 1], env[j]);
				tmp[j + 2] = NULL;
				ft_splitdel(&env);
				if (!(env = (char **)malloc(sizeof(char *) *
								(tab_len(tmp) + 1))))
					return (NULL);
				j = 0;
				while (tmp[j])
				{
					if (!(env[j] = (char *)malloc(sizeof(char) *
									(ft_strlen(tmp[j]) + 1))))
						return (NULL);
					ft_strcpy(env[j], tmp[j]);
					j++;
				}
				env[j] = NULL;
				ft_splitdel(&tmp);
				tmp = NULL;
			}
			else
			{
				j = 0;
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
			}
		}
		i++;
	}
	return (env);
}
