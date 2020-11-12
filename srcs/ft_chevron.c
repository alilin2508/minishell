/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chevron.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 10:53:12 by grigo             #+#    #+#             */
/*   Updated: 2020/11/12 13:56:39 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_nbchevron2(const char *str, int i)
{
	if (i == 0)
	{
		if ((str[i] == '>' && ((str[i + 1] != '>' && str[i + 1] != ' ') ||
			(str[i + 1] == '>' && str[i + 2] != ' '))) ||
			(str[i] == '<' && str[i + 1] != ' '))
			return (1);
	}
	else if ((str[i] == '>' && str[i - 1] != '>' && str[i - 1] != ' ' &&
		str[i + 1] != ' ' && str[i + 1] != '>') || (str[i] == '>' &&
		str[i + 1] == '>' && str[i - 1] != ' ' && str[i + 2] != ' ') ||
			(str[i] == '<' && str[i - 1] != ' ' && str[i + 1] != ' '))
		return (2);
	else if ((str[i] == '>' && str[i + 1] != '>' && str[i - 1] != '>' &&
		(str[i - 1] != ' ' || str[i + 1] != ' ')) || (str[i] == '>' &&
		str[i + 1] == '>' && (str[i - 1] != ' ' || str[i + 2] != ' ')) ||
		(str[i] == '<' && (str[i - 1] != ' ' || str[i + 1] != ' ')))
		return (1);
	return (0);
}

int		ft_spacechevron(char *str, int i)
{
	if (((str[i] == '>' && str[i - 1] != ' ' && str[i - 1] != '>' &&
	str[i - 1] != '\\') ||
	(str[i] == '<' && str[i - 1] != ' ' && str[i - 1] != '\\')))
		return (1);
	else if ((str[i - 1] == '>' && str[i] != ' ' && str[i] != '>' &&
	str[i - 2] != '>' && str[i - 2] != '\\')
	|| (str[i - 1] == '<' && str[i] != ' ' && str[i - 2] != '\\') ||
		(str[i - 1] == '>' && str[i] != ' ' && str[i] != '>' &&
		str[i - 2] == '>' && str[i - 3] != '\\'))
		return (1);
	return (0);
}

int		ft_nbchevron(const char *str)
{
	int		i;
	int		nb;
	char	c;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i++];
			while (str[i] != c && str[i])
			{
				if (str[i] == '>' || str[i] == '<')
					nb += 2;
				i++;
			}
		}
		nb += ft_nbchevron2(str, i);
		i++;
	}
	return (nb);
}

char	*ft_checkredir2(char *str, char *tmp, int i, int j)
{
	int		c;

	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (str[i - 1] == '>' || str[i - 1] == '<')
				tmp[j++] = ' ';
			c = str[i];
			tmp[j++] = str[i++];
			while (str[i] != c)
			{
				if ((str[i] == '>' || str[i] == '<'))
				{
					if (c == '"')
						tmp[j++] = '\\';
					tmp[j++] = '\\';
				}
				tmp[j++] = str[i++];
			}
		}
		if (i != 0 && str[i] != '"' && str[i] != '\'')
			if (ft_spacechevron(str, i))
				tmp[j++] = ' ';
		tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*ft_checkredir(char *str)
{
	char	*tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) +
			ft_nbchevron((const char *)str) + 1))))
		return (NULL);
	tmp = ft_checkredir2(str, tmp, 0, 0);
	free(str);
	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 1))))
		return (NULL);
	ft_strcpy(str, tmp);
	free(tmp);
	return (str);
}
