/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:28:40 by grigo             #+#    #+#             */
/*   Updated: 2020/10/28 12:05:45 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		takepath(char *str, int idx, char *tmp, char **env)
{
	int		i;
	char	*str_tmp;
	char	*tenv;

	i = 0;
	if (!(str_tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (-1);
	while (str[idx] && str[idx] != '$' &&
		str[idx] != ' ' && str[idx] != '"')
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

char	*ft_variables(char *str, int idx, char **env)
{
	char	*tmp;
	char	*tenv;

	if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + PATH_MAX + 1))))
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
	if (str[idx] != '\0')
		ft_strcat(tmp, &str[idx]);
	free(str);
	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 1))))
		return (NULL);
	ft_strcpy(str, tmp);
	free(tmp);
	return (str);
}

/*char	*ft_backslash(char *str, int bsl)
{
	char	*tmp;
	int		i;

	if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(str)))))
		return (NULL);
	i = 0;
	while (i != bsl)
	{
		tmp[i] = str[i];
		i++;
	}
	bsl++;
	while (str[bsl])
		tmp[i++] = str[bsl++];
	tmp[i] = '\0';
	free(str);
	str = NULL;
	if (!(str = (char *)malloc(sizeof(char*) * (ft_strlen(tmp) + 1))))
		return (NULL);
	ft_strcpy(str, tmp);
	free(tmp);
	return (str);
}*/

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
		if (str[i] == '$')
		{
			if (ft_strlen(str) != 1 && str[i + 1] != '\0' && str[i + 1] != ' ')
			{
				if ((str = ft_variables(str, i, env)) == NULL)
					return (NULL);
				i = -1;
			}
		}
		i++;
	}
	return (str);
}
