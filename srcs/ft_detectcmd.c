/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_detectcmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:12:42 by grigo             #+#    #+#             */
/*   Updated: 2020/10/28 13:29:49 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_initf(int f_open[2])
{
	g_cvr[0] = 0;
	g_cvr[1] = 0;
	g_file[0] = 0;
	g_file[1] = 0;
	f_open[0] = 0;
	f_open[1] = 0;
}

void		ft_nextchevron(char **cmd, int i)
{
	if (cmd[i][0] == 1 && cmd[i][1] == '\0')
		cmd[i][0] = '>';
	if (cmd[i][0] == 1 && cmd[i][1] == 1 && cmd[i][2] == '\0')
	{
		cmd[i][0] = '>';
		cmd[i][1] = '>';
	}
	if (cmd[i][0] == 2 && cmd[i][1] == '\0')
		cmd[i][0] = '<';
}

char		**ft_selec_redir(char **cmd, int f_open[2])
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], ">") || !ft_strcmp(cmd[i], ">>"))
		{
			if (!(cmd = my_redir_right(cmd, i, f_open)))
				return (NULL);
			g_cvr[0] = 1;
			f_open[0] = 1;
			i--;
		}
		if (!ft_strcmp(cmd[i], "<"))
		{
			if (!(cmd = my_redir_left(cmd, i, f_open)))
				return (NULL);
			g_cvr[1] = 1;
			f_open[1] = 1;
			i--;
		}
		ft_nextchevron(cmd, i);
		i++;
	}
	return (cmd);
}

char		**detectcmd(char **cmd)
{
	int		f_open[2];

	ft_initf(f_open);
	cmd = ft_selec_redir(cmd, f_open);
	if (g_cvr[0])
	{
		g_fd[0] = dup(STDOUT_FILENO);
		close(STDOUT_FILENO);
		if (dup2(g_file[0], STDOUT_FILENO) == -1)
			write(2, "error: dup2 failed\n", 19);
	}
	if (g_cvr[1])
	{
		g_fd[1] = dup(0);
		close(0);
		if (dup2(g_file[1], 0) == -1)
			write(2, "error: dup2 failed\n", 19);
	}
	return (cmd);
}
