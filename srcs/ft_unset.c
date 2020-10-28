/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:04:24 by grigo             #+#    #+#             */
/*   Updated: 2020/10/28 17:07:53 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**ft_unset(char **cmd, char **env)
{
	int		i;
	int		j;
	int		idx;
	char	**tmp;
	char	*tcmd;

	tmp = NULL;
	i = 1;
	errno = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (!ft_isalnum(cmd[i][j]) && cmd[i][j] != '_')
			{
				ft_puterror("bash: unset: `", cmd[i],
					"': not a valid identifier\n", 1);
				j = -1;
				break ;
			}
			j++;
		}
		if (j != -1)
		{
			if (!(tcmd = (char *)malloc(sizeof(char) *
					(ft_strlen(cmd[i]) + 2))))
				return (NULL);
			j = 0;
			while (cmd[i][j])
			{
				tcmd[j] = cmd[i][j];
				j++;
			}
			tcmd[j] = '=';
			tcmd[j + 1] = '\0';
			if ((idx = ft_checkunset(tcmd, env) - 1) != -1)
			{
				if (!(tmp = (char **)malloc(sizeof(char *) * (tab_len(env)))))
					return (NULL);
				j = 0;
				while (j < idx)
				{
					if (!(tmp[j] = (char *)malloc(sizeof(char) *
							(ft_strlen(env[j]) + 1))))
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
			free(tcmd);
		}
		i++;
	}
	return (env);
}
