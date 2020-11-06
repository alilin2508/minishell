/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:44:50 by grigo             #+#    #+#             */
/*   Updated: 2020/11/06 19:04:41 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		passquotes(const char *str, int i, int c)
{
	while (str[i] != c && str[i])
	{
		if (str[i] == '\\' && c != '\'')
			i++;
		i++;
	}
	if (str[i] == '\0')
		return (-1);
	return (i);
}

int		ft_cword(char *line)
{
	int		i;
	int		nb;

	i = 0;
	nb = 1;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			i = passquotes(line, i, line[i]);
		if (line[i] == ' ')
		{
			while (line[i + 1] == ' ')
				i++;
			nb++;
		}
		i++;
	}
	return (nb);
}

int		ft_sepcount(char *line, char c)
{
	int		len;

	len = 0;
	while (line[len] != c)
		len++;
	return (len + 1);
}

int		tab_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	*my_redirection(char *str)
{
	if (ft_strchr(str, '>') || ft_strchr(str, '<'))
		str = ft_checkredir(str);
	if (ft_strchr(str, '\\'))
		str = ft_checkbackredir(str, 0, 0);
	return (str);
}
