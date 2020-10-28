/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:44:50 by grigo             #+#    #+#             */
/*   Updated: 2020/10/28 12:49:45 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cword(char *line)
{
	int		i;
	int		nb;
	char	sep;

	i = 0;
	nb = 1;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			sep = line[i];
			i++;
			while (line[i] != sep && line[i])
				i++;
		}
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
	return (str);
}
