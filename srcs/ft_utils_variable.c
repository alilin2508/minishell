/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_variable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 12:44:39 by grigo             #+#    #+#             */
/*   Updated: 2020/11/17 13:19:28 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_checkvar(char *str, int i, bool r)
{
	if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '?') &&
		!ft_isdigit(str[i + 1]) && ft_strlen(str) != 1 && str[i + 1] != '\0' &&
		str[i + 1] != ' ' && r)
		return (1);
	return (0);
}

bool	ft_check_var_redir(char *str, int i)
{
	int		idx;

	idx = 0;
	if (str[i] == '$')
	{
		idx = i - 1;
		while (str[idx] == ' ' && idx != 0)
			idx--;
		if ((str[idx] == '>' || str[idx] == '<') && str[idx - 1] == ' ')
			return (false);
	}
	return (true);
}

char	*get_tmp_variable(char *str, int k, char **env, char *tmp)
{
	char	*tenv;

	if (!(tmp = (char *)ft_calloc(sizeof(char),
			(ft_strlen(str) + PATH_MAX + 1))))
		return (NULL);
	while (str[k] != ' ' && str[k] != '"' && str[k])
	{
		if (str[k] == '$')
		{
			if (str[k + 1] != '?')
				k = takepath(str, k + 1, tmp, env) - 1;
			else
			{
				tenv = ft_itoa(errno);
				ft_strcat(tmp, tenv);
				free(tenv);
				k++;
			}
		}
		else
			ft_strccat(tmp, str[k]);
		k++;
	}
	return (tmp);
}

char	*ft_modif_str_vari(char *str, int idx, char *tmp)
{
	char	*tmp2;
	int		k;

	if (!(tmp2 = (char *)ft_calloc(sizeof(char), (ft_strlen(str) + PATH_MAX))))
		return (NULL);
	if (idx != 0)
		ft_strlcpy(tmp2, str, idx + 1);
	ft_strcat(tmp2, tmp);
	free(tmp);
	while (str[idx] != ' ' && str[idx] != '"' && str[idx])
		idx++;
	k = idx;
	while (str[idx] == ' ' && str[idx])
		idx++;
	if (str[idx] != '\0')
		ft_strcat(tmp2, &str[k]);
	free(str);
	str = NULL;
	str = ft_strdup(tmp2);
	free(tmp2);
	return (str);
}

char	*ft_variables3(char *str, int idx, char **env)
{
	char	*tmp;

	tmp = NULL;
	if ((tmp = get_tmp_variable(str, idx, env, tmp)) == NULL)
		return (NULL);
	if (tmp[0] == '\0')
	{
		free(tmp);
		return (str);
	}
	else
	{
		if ((str = ft_modif_str_vari(str, idx, tmp)) == NULL)
			return (NULL);
	}
	printf("str = %s\n", str);
	return (str);
}
