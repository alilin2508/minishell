/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:34:00 by grigo             #+#    #+#             */
/*   Updated: 2020/11/17 14:49:36 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_cmd_creatnull(char **cmd, int j, int k)
{
	if (cmd[j] != NULL)
	{
		cmd[j][k] = '\0';
		cmd[j + 1] = NULL;
	}
	return (cmd);
}

char	*get_str_var(char *str, char *tmp, int idx, int sp)
{
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

int		ft_strcmparg(char *str)
{
	int		i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

char	**ft_strerror(char *str, char **cmd)
{
	ft_puterror("bash: ", str, ": ", errno);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	ft_splitdel(&cmd);
	return (NULL);
}

char	**ft_returncmd(char **cmd, char *mess, int err)
{
	errno = err;
	write(2, mess, ft_strlen(mess));
	ft_splitdel(&cmd);
	return (NULL);
}
