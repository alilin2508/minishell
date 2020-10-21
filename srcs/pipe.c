/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilspipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:29:28 by grigo             #+#    #+#             */
/*   Updated: 2020/10/20 16:56:09 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_nbpipe2(const char *str)
{
	int		i;
	int		nb;
	char	c;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i])
				i++;
		}
		if (str[i] == '|')
			nb++;
		i++;
	}
	return (nb);
}

void		my_pipe(char **cmd, char ***env)
{
	int		pfd[2];
	int		fd_in;
	int		i;
	int 	status;

	fd_in = 0;
	i = 0;
	status = 0;
	while (cmd[i] != 0)
	{
		pipe(pfd);
		if ((g_pid[1] = fork()) == -1)
			exit(EXIT_FAILURE);
		else if (g_pid[1] == 0)
		{
			dup2(fd_in, 0);
			if (cmd[i + 1] != NULL)
				dup2(pfd[1], 1);
			close(pfd[0]);
			ft_commande(cmd[i], env);
			exit(EXIT_FAILURE);
		}
		else
		{
			if (!ft_strcmp(cmd[i], "cat"))
			{
				waitpid(g_pid[1], NULL, WSTOPPED);
				//kill(g_pid[1], SIGTERM);
				//waitpid(g_pid[1], NULL, WNOHANG);
			}
			wait(NULL);
			close(pfd[1]);
			fd_in = pfd[0];
			i++;
		}
	}
}

void		ft_pipe(char *str, char ***env, int nb)
{
	char	**command;
	int		i;
	int		j;
	int		first;
	int 	c;

	if (!(command = (char **)malloc(sizeof(char *) * (nb + 2))))
		return ;
	i = 0;
	j = 0;
	first = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i])
				i++;
		}
		if (str[i] == '|')
		{
			c = i;
			while (str[c - 1] == ' ')
				c--;
			if (!(command[j] = (char *)malloc(sizeof(char) * (c - first) + 1)))
				return ;
			ft_strlcpy(command[j], &str[first], c - first + 1);
			while (str[i + 1] == ' ')
				i++;
			first = i + 1;
			j++;
		}
		i++;
	}
	if (!(command[j] = (char *)malloc(sizeof(char) * (i - first) + 1)))
		return ;
	ft_strlcpy(command[j], &str[first], i - first + 1);
	j++;
	command[j] = NULL;
	my_pipe(command, env);
	ft_splitdel(&command);
}
