/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 10:30:45 by grigo             #+#    #+#             */
/*   Updated: 2020/10/28 17:14:10 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_execution(char **cmd)
{
	int		status;

	status = 0;
	if ((g_pid[0] = fork()) == -1)
		write(2, "fork fail\n", 10);
	else if (g_pid[0] > 0)
	{
		waitpid(g_pid[0], &status, 0);
		kill(g_pid[0], SIGTERM);
	}
	else
	{
		if (execve(cmd[0], cmd, NULL) == -1)
			ft_puterror("bash: ", cmd[0], ": command not found\n", 127);
		exit(EXIT_FAILURE);
	}
}

void	exect_built_commande(char **cmd, char ***env)
{
	if (!ft_strcmp(cmd[0], "cd"))
		errno = my_cd(cmd[1], env);
	else if (!ft_strcmp(cmd[0], "env"))
		errno = environment(cmd, *env);
	else if (!ft_strcmp(cmd[0], "pwd"))
		errno = position();
	else if (!ft_strcmp(cmd[0], "export"))
		*env = ft_export(&cmd[1], *env);
	else if (!ft_strcmp(cmd[0], "unset"))
		*env = ft_unset(cmd, *env);
	else if (!ft_strcmp(cmd[0], "echo"))
		errno = ft_echo(cmd);
}

int		built_command(char *cmd)
{
	char	*build_com[7];
	int		i;

	build_com[0] = "cd";
	build_com[1] = "env";
	build_com[2] = "pwd";
	build_com[3] = "export";
	build_com[4] = "unset";
	build_com[5] = "echo";
	build_com[6] = NULL;
	i = 0;
	while (build_com[i])
	{
		if (ft_strcmp(build_com[i], cmd) == 0)
			return (1);
		i++;
	}
	return (0);
}

int		main(int ac, char **av, char **env)
{
	char	*line;
	char	**envi;

	(void)ac;
	(void)av;
	line = NULL;
	envi = ft_getenv(env);
	signal(SIGINT, recovery);
	signal(SIGQUIT, end);
	while (1)
	{
		g_pid[0] = 0;
		write(1, "\033[1;34m$alilin> \033[0;37m", 23);
		if (get_next_line(0, &line) == 0)
			ft_exit(NULL);
		ft_precommande(line, &envi);
		free(line);
		line = NULL;
	}
	return (0);
}
