/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:08:39 by grigo             #+#    #+#             */
/*   Updated: 2020/11/10 16:34:56 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end(int sig)
{
	(void)sig;
	if (g_pid[0] != 0 && g_pid[1] == 0)
	{
		write(2, "Quit: 3\n", 8);
		kill(g_pid[0], SIGQUIT);
	}
	else if (g_pid[1] != 0)
		kill(g_pid[1], SIGINT);
	else
		ft_putstr("\b \b\b \b");
}

void	recovery(int sig)
{
	(void)sig;
	if (g_pid[0] == 0 && g_pid[1] == 0)
	{
		ft_putstr("\b \b\b \b\n");
		write(0, "\033[1;34m$alilin> \033[0;37m", 23);
		errno = 1;
	}
	else
	{
		if (g_pid[1] != 0)
			kill(g_pid[1], SIGINT);
		else
			kill(g_pid[0], SIGINT);
		write(1, "\n", 1);
		errno = 130;
	}
}

int		ft_exit(char **cmd)
{
	if (cmd != NULL)
	{
		write(0, "exit\n", 5);
		if (cmd[1] != NULL && ft_strisdigit(cmd[1]))
		{
			if (cmd[2] != NULL)
			{
				write(2, "bash: exit: too many arguments\n", 31);
				return (1);
			}
			errno = ft_atoi(cmd[1]);
			if (errno == -1 && ft_strcmp(cmd[1], "-1"))
				ft_puterror("bash: exit: ", cmd[1],
					": numeric argument required\n", 255);
		}
		else if (cmd[1] != NULL)
			ft_puterror("bash: exit: ", cmd[1], ": numeric argument required\n", 255);
		ft_splitdel(&cmd);
		//system("leaks minishell");
		exit(errno);
	}
	ft_putstr("  \b\b \b");
	write(0, "\n", 1);
	exit(errno);
}
