/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:08:39 by grigo             #+#    #+#             */
/*   Updated: 2020/10/20 13:13:43 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end(int sig)
{
	(void)sig;
	if (g_pid != 0)
	{
		write(2, "Quit: 3\n", 8);
		kill(g_pid, SIGQUIT);
	}
	else
		ft_putstr("\b \b\b \b");
}

void	recovery(int sig)
{
	(void)sig;
	if (g_pid == 0)
	{
		ft_putstr("\b \b\b \b\n");
		write(1, "\033[1;34m$alilin> \033[0;37m", 23);
	}
	else
	{
		kill(g_pid, SIGINT);
		write(1, "\n", 1);
	}
}
