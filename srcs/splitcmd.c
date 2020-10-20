/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 14:47:41 by grigo             #+#    #+#             */
/*   Updated: 2020/10/20 15:45:34 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_nb_cmd(const char *line)
{
	int		i;
	int		nb;
	char	c;

	i = 0;
	nb = 1;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			c = line[i];
			i++;
			while (line[i] && line[i] != c)
				i++;
			if (line[i] == '\0')
				return (-1);
		}
		if (line[i] == ';')
			nb++;
		if (line[i] == '\\')
			i++;
		i++;
	}
	return (nb);
}

char	*ft_takecmd(char *str, int first, int last)
{
	int		i;
	char	*s;

	while (str[first] == ';' || str[first] == ' ')
		first++;
	if (str[first] == '\0')
		return (NULL);
	if (!(s = (char *)malloc(sizeof(char) * (last - first + 2))))
		return (NULL);
	i = 0;
	while (first < last)
	{
		s[i] = str[first];
		i++;
		first++;
	}
	s[i] = '\0';
	return (s);
}

int		ft_strnext(char *str, int j)
{
	char	c;

	c = str[j];
	j++;
	while (str[j] && str[j] != c)
	{
		if (str[j] == '>' && str[j - 1] == c && str[j + 1] == c &&
				str[j - 2] == ' ')
			str[j] = 1;
		else if (str[j] == '<' && str[j - 1] == c &&
				str[j + 1] == c && str[j - 2] == ' ')
			str[j] = 2;
		else if (str[j] == '>' && str[j + 1] == '>' &&
				str[j - 1] == c && str[j + 2] == c &&
				str[j - 2] == ' ')
		{
			str[j + 1] = 1;
			str[j] = 1;
		}
		j++;
	}
	return (j);
}

char	**ft_splitcmd(char *str)
{
	char	**tab;
	int		first;
	int		i;
	int		j;

	if (ft_nb_cmd(str) == -1)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char*) * (ft_nb_cmd(str) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	first = 0;
	while (str[j])
	{
		if (str[j] == '"' || str[j] == '\'')
			j += ft_strnext(str, j);
		if (str[j] == ';')
		{
			if ((tab[i++] = ft_takecmd(str, first, j)) == NULL)
			{
				tab[i] = NULL;
				i = -1;
				break ;
			}
			j++;
			while (str[j] == ' ' && str[j] == ';')
				j++;
			first = j;
		}
		if (str[j] == '\\')
			j++;
		j++;
	}
	if (i != -1)
	{
		tab[i] = ft_takecmd(str, first, j);
		tab[i + 1] = NULL;
	}
	return (tab);
}
