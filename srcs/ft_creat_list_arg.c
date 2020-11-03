/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_list_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:56:47 by grigo             #+#    #+#             */
/*   Updated: 2020/10/29 13:30:35 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	ft_passpace(char *line, int idx)
{
	while (line[idx] == ' ')
		idx++;
	if (line[idx] == '\0')
		return (0);
	return (1);
}

char	**creat_list_arg2(char *line, char **cmd, int i, int j)
{
	int 	k;
	int		c;

	k = 0;
	c = '\0';
	while (line[i])
	{
		if (line[i] == ' ')
		{
			cmd[j][k] = '\0';
			j += 1;
			cmd[j] = NULL;
			k = 0;
			while(line[i] == ' ')
				i++;
			if (line[i] == '\0')
				break ;
			if (!(cmd[j] = (char *)ft_calloc(sizeof(char), (ft_strlen(&line[i]) + 1))))
				return (NULL);
		}
		if (line[i] == '\'' || line[i] == '"')
		{
			c = line[i];
			i++;
			while (line[i] != c && line[i])
			{
				if ((line[i] == '\\' && c == '"') && (line[i + 1] == '\\' ||
							line[i + 1] == '"' || line[i + 1] == '$'))
					i++;
				cmd[j][k++] = line[i++];
			}
		}
		if (line[i] == '\\' && line[i + 1] != '>' && line[i + 1] != '<')
			i++;
		if (line[i] != c)
			cmd[j][k++] = line[i];
		i++;
	}
	if (cmd[j] != NULL)
	{
		cmd[j][k] = '\0';
		cmd[j + 1] = NULL;
	}
	return (cmd);
}

char	**creat_list_arg(char *line)
{
	char	**commande;

	if (!(commande = (char **)malloc(sizeof(char *) * (ft_cword(line) + 1))))
		return (NULL);
	if (!(commande[0] = (char *)ft_calloc(sizeof(char), (ft_strlen(line) + 1))))
		return (NULL);
	commande = creat_list_arg2(line, commande, 0, 0);
	return (commande);
}
