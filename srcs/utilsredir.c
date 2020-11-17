/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsredir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 16:35:30 by grigo             #+#    #+#             */
/*   Updated: 2020/11/15 16:35:31 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**open_simple_redir(char **cmd, int f_open[2], int idx)
{
	if (f_open[0] == 1)
		close(g_file[0]);
	if (cmd[idx + 1][0] == '$' && ft_strlen(cmd[idx + 1]) != 1)
	{
		ft_puterror("bash: ", cmd[idx + 1], ": ambiguous redirect\n", 1);
		ft_splitdel(&cmd);
		errno = 1;
		return (NULL);
	}
	if ((g_file[0] = open(cmd[idx + 1], O_CREAT | O_WRONLY | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		return (ft_strerror(cmd[idx + 1], cmd));
	return (cmd);
}

char	**open_double_redir(char **cmd, int f_open[2], int idx)
{
	if (f_open[0])
		close(g_file[0]);
	if (cmd[idx + 1][0] == '$' && ft_strlen(cmd[idx + 1]) != 1)
	{
		ft_puterror("bash: ", cmd[idx + 1], ": ambiguous redirect\n", 1);
		ft_splitdel(&cmd);
		errno = 1;
		return (NULL);
	}
	if ((g_file[0] = open(cmd[idx + 1], O_CREAT | O_WRONLY | O_APPEND,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		return (ft_strerror(cmd[idx + 1], cmd));
	return (cmd);
}
