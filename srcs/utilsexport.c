/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsexport.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:37:29 by grigo             #+#    #+#             */
/*   Updated: 2020/10/29 10:55:40 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pass_space(char *str, int i)
{
	while (str[i + 1] == ' ')
		i++;
	return (i);
}

int 	delspace(char *str, int c)
{
	while (str[c - 1] == ' ')
		c--;
	return (c);
}

int		ft_checkex2(char *cmd, char **env)
{
	int		i;
	int		len;

	i = 0;
	while (cmd[i] != '=')
		i++;
	len = i;
	while (env[i])
	{
		if (ft_strncmp(cmd, env[i], len) == 0)
			return (0);
		i++;
	}
	return (1);
}

int		ft_checkunset(char *cmd, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], cmd, ft_strlen(cmd)))
			return (i + 1);
		i++;
	}
	return (0);
}

int		ft_nbpipe2(const char *str)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if ((i = passquotes(str, i + 1, str[i])) == -1)
				break ;
		}
		if (str[i] == '|')
			nb++;
		if (str[i] == '\\')
			i++;
		i++;
	}
	return (nb);
}
