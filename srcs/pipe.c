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

void   			my_pipe(char **cmd, char ***env)
{
	int 		pfd[2];
	int			ppfd[2];
	pid_t   ppid[2];
	int  		fd_in;
	int 		i;

	fd_in = 0;
	i = 0;
	while (cmd[i] != 0)
	{
		pipe(pfd);
		if ((ppid[0] = fork()) == -1)
			exit(EXIT_FAILURE);
		else if (ppid[0] == 0)
		{
			dup2(fd_in, 0);
			close(pfd[0]);
			if (cmd[i + 1] != NULL)
				dup2(pfd[1], STDOUT_FILENO);
			close(pfd[1]);
			ft_command(cmd[i], env);
			exit(EXIT_FAILURE);
		}
		else
		{
			if (cmd[i + 1] != NULL)
			{
				pipe(ppfd);
				if ((ppid[1] = fork()) == -1)
					exit(EXIT_FAILURE);
				else if (ppid[1] == 0)
				{
					close(pfd[1]);
					dup2(pfd[0], STDIN_FILENO);
					close(pfd[0]);
					close(ppfd[0]);
					if (cmd[i + 2] != NULL)
						dup2(ppfd[1], STDOUT_FILENO);
					close(ppfd[1]);
					ft_command(cmd[i + 1], env);
					exit(EXIT_FAILURE);
				}
				else
				{
					close(pfd[0]);
					close(pfd[1]);
					close(ppfd[1]);
					fd_in = dup(ppfd[0]);
					close(ppfd[0]);
					i++;
				}
			}
			wait(NULL);
			wait(NULL);
		}
		i++;
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
