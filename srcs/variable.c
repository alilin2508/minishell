/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:28:40 by grigo             #+#    #+#             */
/*   Updated: 2020/11/10 11:50:45 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		takepath(char *str, int idx, char *tmp, char **env)
{
	int		i;
	char	*str_tmp;
	char	*tenv;

	i = 0;
	if (!(str_tmp = (char *)ft_calloc(sizeof(char), (ft_strlen(str) + 1))))
		return (-1);
	while (str[idx] && str[idx] != '$' && str[idx] != ' ' &&
	(ft_isalnum(str[idx]) || str[idx] == '_'))
	{
		str_tmp[i] = str[idx];
		idx++;
		i++;
	}
	str_tmp[i] = '=';
	str_tmp[i + 1] = '\0';
	if ((tenv = my_getenv(env, str_tmp)) != NULL)
		ft_strcat(tmp, tenv);
	tenv = NULL;
	free(str_tmp);
	str_tmp = NULL;
	return (idx);
}

char	*ft_spaceredir(char *str, char *tmp, int idx, int i)
{
	int		j;

	j = 0;
	while (str[i])
	{
		if (i == idx || i == idx + 1)
		{
			tmp[j] = ' ';
			j++;
		}
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	free(str);
	str = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	return (str);
}

char	*ft_checkbackredir(char *str, int i, int nb)
{
	char	*tmp;

	tmp = NULL;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = passquotes(str, i + 1, str[i]);
		while (str[i] == '\\')
		{
			nb++;
			i++;
		}
		if ((str[i] == '>' || str[i] == '<') && nb != 0 && nb % 2 == 0)
		{
			if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + 3))))
				return (NULL);
			str = ft_spaceredir(str, tmp, i, 0);
			i += 1;
		}
		else
			nb = 0;
		i++;
	}
	return (str);
}

char	*ft_variables(char *str, int idx, char **env, int sp)
{
	char	*tmp;
	char	*tenv;

	if (!(tmp = (char *)ft_calloc(sizeof(char), (ft_strlen(str) + PATH_MAX + 1))))
		return (NULL);
	if (idx != 0)
		ft_strlcpy(tmp, str, idx + 1);
	idx++;
	if (str[idx] != '?')
		idx = takepath(str, idx, tmp, env);
	else
	{
		tenv = ft_itoa(errno);
		ft_strcat(tmp, tenv);
		free(tenv);
		idx++;
	}
	sp = idx;
	while (str[sp] == ' ' && str[sp])
		sp++;
	if (str[sp] != '\0')
		ft_strcat(tmp, &str[idx]);
	free(str);
	if (!(str = (char *)ft_calloc(sizeof(char), (ft_strlen(tmp) + 1))))
		return (NULL);
	ft_strcpy(str, tmp);
	free(tmp);
	return (str);
}

char	*variables1(char *str, char **env)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i += 2;
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		if (str[i] == '$' && str[i + 1] != '$' && str[i + 1] != '"' &&
				!ft_isdigit(str[i + 1]) && str[i + 1] != '=')
		{
			if (ft_strlen(str) != 1 && str[i + 1] != '\0' && str[i + 1] != ' ')
			{
				if ((str = ft_variables(str, i, env, 0)) == NULL)
					return (NULL);
				i--;
			}
		}
		i++;
	}
	return (str);
}
