/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:29:28 by grigo             #+#    #+#             */
/*   Updated: 2020/10/28 11:02:29 by grigo            ###   ########.fr       */
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

static int	execution(char *cmd, int p_in[2], int p_out[2], char ***env)
{
	g_pid[1] = fork();
	if (g_pid[1] == -1)
		exit(EXIT_FAILURE);
	else if (g_pid[1] == 0)
	{
		if (p_in[0] != -1 && p_in[1] != -1)
		{
			close(p_in[1]);
			dup2(p_in[0], STDIN_FILENO);
		}
		if (p_out[0] != -1 && p_out[1] != -1)
		{
			close(p_out[0]);
			dup2(p_out[1], STDOUT_FILENO);
		}
		close(p_in[0]);
		ft_command(cmd, env);
		exit(EXIT_FAILURE);
	}
	return (g_pid[1]);
}

static int	preexecution(char **cmd, int p_in[2], int p_out[2], char ***env)
{
	int i;
	int nb_cmd;

	nb_cmd = tab_len(cmd);
	i = 0;
	while (cmd[i])
	{
		if (i < nb_cmd - 1)
			pipe(p_out);
		execution(cmd[i], p_in, p_out, env);
		close(p_in[1]);
		close(p_in[0]);
		if (i < nb_cmd - 1)
		{
			p_in[0] = p_out[0];
			p_in[1] = p_out[1];
		}
		else
		{
			p_out[0] = -1;
			p_out[1] = -1;
		}
		i++;
	}
	return (g_pid[1]);
}

void		my_pipe(char **cmd, char ***env)
{
	int		p_in[2];
	int		p_out[2];

	p_in[0] = -1;
	p_in[1] = -1;
	p_out[0] = -1;
	p_out[1] = -1;
	preexecution(cmd, p_in, p_out, env);
	close(p_out[0]);
	close(p_out[1]);
	while (wait(NULL) > 0)
	{
	}
}

void		ft_pipe(char *str, char ***env, int nb)
{
	char	**command;
	int		i;
	int		j;
	int		first;
	int		c;

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
