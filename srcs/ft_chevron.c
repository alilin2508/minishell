/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chevron.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 10:53:12 by grigo             #+#    #+#             */
/*   Updated: 2020/10/28 11:15:41 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				i++;
		}
		if ((str[i] == '>' && str[i - 1] != '>' && str[i - 1] != ' ' &&
			str[i + 1] != ' ' && str[i + 1] != '>') || (str[i] == '>' &&
			str[i + 1] == '>' && str[i - 1] != ' ' && str[i + 2] != ' ') ||
				(str[i] == '<' && str[i - 1] != ' ' && str[i + 1] != ' '))
			nb += 2;
		else if ((str[i] == '>' && str[i + 1] != '>' && str[i - 1] != '>' &&
			(str[i - 1] != ' ' || str[i + 1] != ' ')) || (str[i] == '>' &&
			str[i + 1] == '>' && (str[i - 1] != ' ' || str[i + 2] != ' ')) ||
			(str[i] == '<' && (str[i - 1] != ' ' || str[i + 1] != ' ')))
			nb++;
		i++;
	}
	return (nb);
}

char	*ft_chevronspace(char *str)
{
	char	*tmp;
	int		i;
	int		j;
	char	c;

	if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) +
			ft_nbchevron((const char *)str) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i++];
			while (str[i] != c && str[i])
				i++;
		}
		if (i == 0)
		{
			if (str[i] == '>' && str[i + 1] != '>' && str[i + 1] != ' ')
			{
				tmp[j] = '>';
				tmp[j + 1] = ' ';
				j += 2;
				i++;
			}
			else if (str[i] == '<' && str[i + 1] != ' ')
			{
				tmp[j] = '<';
				tmp[j + 1] = ' ';
				j += 2;
				i++;
			}
		}
		else if (((str[i] == '>' && str[i - 1] != ' ' && str[i - 1] != '>')
		|| (str[i] == '<' && str[i - 1] != ' ')) && i != 0)
		{
			tmp[j] = ' ';
			j++;
		}
		else if ((str[i - 1] == '>' && str[i] != ' ' && str[i] != '>')
		|| (str[i - 1] == '<' && str[i] != ' '))
		{
			tmp[j] = ' ';
			j++;
		}
		tmp[j] = str[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	free(str);
	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 1))))
		return (NULL);
	ft_strcpy(str, tmp);
	free(tmp);
	return (str);
}

char	*ft_checkredir(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i])
				i++;
		}
		if (i != 0)
		{
			if ((str[i - 1] != '>' && str[i] == '>' && str[i + 1] != '>'
			&& (str[i + 1] != ' ' || str[i - 1] != ' '))
			|| (str[i] == '>' && str[i + 1] == '>'
			&& (str[i + 2] != ' ' || str[i - 1] != ' '))
			|| (str[i] == '<' && (str[i - 1] != ' ' || str[i + 1] != ' ')))
			{
				str = ft_chevronspace(str);
				break ;
			}
		}
		else
		{
			if ((str[i] == '>' && ((str[i + 1] != '>' && str[i + 1] != ' ') ||
				(str[i + 1] == '>' && str[i + 2] != ' '))) ||
				(str[i] == '<' && str[i + 1] != ' '))
			{
				str = ft_chevronspace(str);
				break ;
			}
		}
		i++;
	}
	return (str);
}
