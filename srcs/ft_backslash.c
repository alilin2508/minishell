/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_backslash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:48:11 by grigo             #+#    #+#             */
/*   Updated: 2020/11/12 13:48:13 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_deletbackslash(char *cmd, char *tmp, int i, int j)
{
	while (cmd[i])
	{
		if (cmd[i] == '\\' && (cmd[i + 1] == '>' || cmd[i + 1] == '<'))
			i++;
		tmp[j++] = cmd[i++];
	}
	tmp[j] = '\0';
	free(cmd);
	if (!(cmd = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 1))))
		return (NULL);
	ft_strcpy(cmd, tmp);
	free(tmp);
	tmp = NULL;
	return (cmd);
}

char	**ft_backslash(char **cmd, int i)
{
	char	*tmp;

	tmp = NULL;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '\\'))
		{
			if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(cmd[i]) + 1))))
				return (NULL);
			cmd[i] = ft_deletbackslash(cmd[i], tmp, 0, 0);
		}
		i++;
	}
	return (cmd);
}
