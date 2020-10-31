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

char	**creat_list_arg2(char *line, char **commande, int i, int j)
{
	int		first;

	first = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			commande[j] = ft_strncat(commande[j], &line[first], i - first);
			first = i + 1;
			commande[j] = ft_strncat(commande[j], &line[first],
				ft_sepcount(&line[first], line[i]) - 1);
			i += ft_sepcount(&line[first], line[i]);
			first = i + 1;
		}
		if (line[i] == ' ')
		{
			if (!ft_passpace(line, i))
				break ;
			commande[j] = ft_strncat(commande[j], &line[first], i - first);
			j++;
			while (line[i + 1] == ' ')
				i++;
			first = i + 1;
			if (line[i + 1] != '\0')
				if (!(commande[j] = (char *)ft_calloc(sizeof(char),
						(ft_strlen(line) + 1))))
					return (NULL);
		}
		if (line[i] == '\\')
			i++;
		i++;
	}
	if (first != i)
		commande[j] = ft_strncat(commande[j], &line[first], i - first);
	commande[j + 1] = NULL;
	return (commande);
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
