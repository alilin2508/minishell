/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:44:07 by grigo             #+#    #+#             */
/*   Updated: 2020/11/13 12:50:22 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**tmp_delet(char **cmd, int idx)
{
	int		i;
	int		j;
	char	**tmp;

	if (!(tmp = (char **)malloc(sizeof(char *) * (tab_len(cmd) - 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (i != idx && i != idx + 1)
		{
			if (!(tmp[j] = (char *)malloc(sizeof(char) *
					(ft_strlen(cmd[i]) + 1))))
				return (NULL);
			ft_strcpy(tmp[j], cmd[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}

char		**delet_chevron(char **cmd, int idx)
{
	int		i;
	char	**tmp;

	tmp = tmp_delet(cmd, idx);
	ft_splitdel(&cmd);
	if (!(cmd = (char **)malloc(sizeof(char*) * (tab_len(tmp) + 1))))
		return (NULL);
	i = 0;
	while (tmp[i])
	{
		if (!(cmd[i] = (char *)malloc(sizeof(char) * (ft_strlen(tmp[i]) + 1))))
			return (NULL);
		ft_strcpy(cmd[i], tmp[i]);
		i++;
	}
	cmd[i] = NULL;
	ft_splitdel(&tmp);
	if (i == 0)
	{
		ft_splitdel(&cmd);
		return (NULL);
	}
	return (cmd);
}

char		**my_redir_left(char **cmd, int idx, int f_open[2])
{
	if (f_open[1])
		close(g_file[1]);
	if (cmd[idx + 1] != NULL)
	{
		if ((g_file[1] = open(cmd[idx + 1], O_RDONLY)) == -1)
		{
			ft_puterror("bash: ", cmd[idx + 1],
				": No such file or directory\n", errno);
			ft_splitdel(&cmd);
			return (NULL);
		}
		f_open[1] = 1;
	}
	cmd = delet_chevron(cmd, idx);
	return (cmd);
}

char		**my_redir_right(char **cmd, int idx, int f_open[2])
{
	if (!ft_strcmp(cmd[idx], ">"))
	{
		if (f_open[0] == 1)
			close(g_file[0]);
		if ((g_file[0] = open(cmd[idx + 1], O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			return (ft_strerror(cmd[idx + 1], cmd));
		else
			f_open[0] = 1;
	}
	else if (!ft_strcmp(cmd[idx], ">>"))
	{
		if (f_open[0])
			close(g_file[0]);
		if ((g_file[0] = open(cmd[idx + 1], O_CREAT | O_WRONLY | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			return (ft_strerror(cmd[idx + 1], cmd));
		else
			f_open[0] = 1;
	}
	cmd = delet_chevron(cmd, idx);
	return (cmd);
}
