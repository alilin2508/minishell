/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_list_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:56:47 by grigo             #+#    #+#             */
/*   Updated: 2020/10/28 17:02:34 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**creat_list_arg(char *line)
{
	char	**commande;
	int		i;
	int		j;
	int		first;

	if (!(commande = (char **)malloc(sizeof(char *) * (ft_cword(line) + 1))))
		return (NULL);
	i = 0;
	first = 0;
	j = 0;
	if (!(commande[j] = (char *)ft_calloc(sizeof(char), (ft_strlen(line) + 1))))
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (i != first)
			{
				commande[j] = ft_strncat(commande[j], &line[first], i - first);
				i++;
				first = i;
				commande[j] = ft_strncat(commande[j], &line[first], ft_sepcount(&line[first], line[i - 1]) - 1);
				i += ft_sepcount(&line[first], line[i - 1]);
				first = i;
				i--;
			}
			else
			{
				i++;
				commande[j] = ft_strncat(commande[j], &line[i], ft_sepcount(&line[i], line[i - 1]) - 1);
				i += ft_sepcount(&line[i], line[i - 1]);
				first = i;
				i--;
			}
		}
		if (line[i] == ' ')
		{
			if (line[i + 1] == '\0')
				break ;
			commande[j] = ft_strncat(commande[j], &line[first], i - first);
			while (line[i + 1] == ' ')
				i++;
			first = i + 1;
			j++;
			if (line[i + 1] != '\0')
				if (!(commande[j] = (char *)ft_calloc(sizeof(char), (ft_strlen(line) + 1))))
					return (NULL);
		}
		i++;
	}
	if (first != i)
	{
		commande[j] = ft_strncat(commande[j], &line[first], i - first);
		commande[j + 1] = NULL;
	}
	else
		commande[j + 1] = NULL;
	return (commande);
}
