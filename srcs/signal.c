/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:08:39 by grigo             #+#    #+#             */
/*   Updated: 2020/10/28 12:08:56 by grigo            ###   ########.fr       */
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
	{
		kill(g_pid[1], SIGINT);
	}
	else
		ft_putstr("\b \b\b \b");
}

void	recovery(int sig)
{
	(void)sig;
	if (g_pid[0] == 0 && g_pid[1] == 0)
	{
		ft_putstr("\b \b\b \b\n");
		write(1, "\033[1;34m$alilin> \033[0;37m", 23);
	}
	else
	{
		if (g_pid[1] != 0)
			kill(g_pid[1], SIGINT);
		else
			kill(g_pid[0], SIGINT);
		write(1, "\n", 1);
	}
}

int		ft_exit(char **commande)
{
	int		ex;

	ex = 0;
	if (commande != NULL)
	{
		if (commande[1] != NULL && ft_isdigit(commande[1][0]))
			ex = ft_atoi(commande[1]);
		ft_splitdel(&commande);
		write(1, "TROP BIEN CE SHELL\n", 19);
		system("leaks minishell");
		exit(ex);
	}
	ft_putstr("  \b\b \b");
	write(1, "\n", 1);
	exit(ex);
}
