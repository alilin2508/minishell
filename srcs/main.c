/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 10:30:45 by grigo             #+#    #+#             */
/*   Updated: 2020/08/26 10:32:46 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _CRTDBG_MAP_ALLOC
#include "minishell.h"

void environment(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_putstr(env[i]);
		write(1, "\n", 1);
		i++;
	}
}

size_t path_max(char **env)
{
	int i;
	size_t max;

	i = 0;
	max = 0;
	while (env[i])
	{
		if (ft_strlen(env[i]) >= max)
			max = ft_strlen(env[i]);
		i++;
	}
	return (max);
}

void position(char **env)
{
	char *buff;
	char *path;

	buff = NULL;
	if (!(path = malloc(sizeof(char) * path_max(env))))
		return;
	path = getcwd(buff, sizeof(path));
	free(buff);
	ft_putstr(path);
	write(1, "\n", 1);
	free(path);
}

void my_cd(const char *path)
{
	if (chdir(path) == -1)
		perror("chdir()");
}

char **ft_getenv(char **env)
{
	char 	**envi;
	int 	i;

	i = 0;
	while (env[i])
		i++;
	if (!(envi = (char**)malloc(sizeof(env) * i + 1)))
		return (0);
	i = 0;
	while (env[i])
	{
		if (!(envi[i] = (char *)malloc(sizeof(char *) * ft_strlen(env[i]) + 1)))
			return (0);
		ft_strlcpy(envi[i], env[i], ft_strlen(env[i]) + 1);
		i++;
	}
	envi[i] = NULL;
	return(envi);
}

char *my_getenv(char **env, char *path)
{
	int i;
	char *usable;

	usable = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], path, ft_strlen(path)) == 0)
		{
			if (!(usable = (char *)malloc(sizeof(char) * ft_strlen(env[i]) - ft_strlen(path))))
				return(0);
			usable = &env[i][ft_strlen(path)+1];
			break ;
		}
		i++;
	}
	return (usable);
}

int ft_access(char *bin)
{
	int fd;

	if ((fd = open(bin, O_RDONLY)) > 0)
		return (0);
	else
		return (-1);
}

static bool get_path(char **cmd, char **env)
{
	char	*path;
	char	*bin;
	char	**split_path;
	int 	i;

	bin = NULL;
	path = NULL;
	split_path = NULL;
	if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) != 0)
	{
		for (int i = 0; env[i]; i++) {
			if (!strncmp(env[i], "PATH=", 5)) {
				path = strdup(&env[i][5]);
				break ;
			}
		}
		if (path == NULL)
			return (false);
		split_path = ft_split(path, ':');
		free(path);
		path = NULL;
		i = 0;
		while (split_path[i])
		{
			bin = (char *)ft_calloc(sizeof(char), (ft_strlen(split_path[i]) + 1 + ft_strlen(cmd[0])) + 1);
			if (bin == NULL)
				break ;
			ft_strcat(bin, split_path[i]);
			ft_strcat(bin, "/");
			ft_strcat(bin, cmd[0]);
			if (ft_access(bin) == 0)
				break ;
			free(bin);
			bin = NULL;
			i++;
		}
		ft_splitdel(&split_path);
		if (bin != NULL)
		{
			free(cmd[0]);
			cmd[0] = bin;
		}
	}
	else
	{
		free(path);
		path = NULL;
		return (true);
	}

	return (bin == NULL ? false : true);
}

static void	cmd_execution(char **cmd)
{
	pid_t	pid;
	int		status;

	pid = 0;
	status = 0;
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(cmd[0], cmd, NULL) == -1)
		{
			write(1, "zsh: No such file or directory: ", 32);
			ft_putstr(cmd[0]);
			write(1, "\n", 1);
		}
		exit(EXIT_FAILURE);
	}
}

static void exect_built_commande(char **cmd, char **env)
{
	if (!ft_strcmp(cmd[0], "cd"))
		my_cd(cmd[1]);
	else if (!ft_strcmp(cmd[0], "env"))
		environment(env);
	else if (!ft_strcmp(cmd[0], "pwd"))
		position(env);
}

int 				built_command(char *cmd)
{
	char	*build_com[] = {"cd", "env", "pwd", NULL};
	int 	i;

	i = 0;
	while (build_com[i])
	{
		if (ft_strcmp(build_com[i], cmd) == 0)
			return (1);
		i++;
	}
	return (0);
}

int                ft_commande(char *line, char **env)
{
  char    **commande;
	char		**tenv;

	commande = NULL;
	tenv = NULL;
  commande = ft_split(line, ' ');
	if (commande[0] == NULL)
		write(1, "", 0);
	else if (ft_strcmp(commande[0], "exit()") == 0)
	{
    ft_splitdel(&commande);
		system("leaks minishell");
		exit(0);
  }
	else if (built_command(commande[0]) == 1)
		exect_built_commande(commande, env);
	else
	{
		tenv = ft_getenv(env);
		if (get_path(commande, tenv) == true)
			cmd_execution(commande);
		else
		{
			write(1, "zsh: command not found: ", 25);
			ft_putstr(commande[0]);
			write(1, "\n", 1);
		}
		ft_splitdel(&tenv);
		tenv = NULL;
	}
	ft_splitdel(&commande);
	return (1);
}

int					main(int ac, char **av, char **env)
{
	char	*line;

	(void)ac;
	(void)av;
	line = NULL;
	while (1)
	{
		write(1, "$alilin> ", 9);
		get_next_line(0, &line);
    ft_commande(line, env);
		free(line);
	}
	system("leaks minishell");
	return (0);
}
