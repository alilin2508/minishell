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

#include "minishell.h"

/**void environment(char **env)
{
	int i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
	return (0);
}

void position(char **env)
{

}**/

char **ft_getenv(char **env)
{
	char 	**envi;
	int 	i;

	i = 0;
	if (!(envi = (char**)malloc(sizeof(env))))
		return (0);
	while (env[i])
	{
		if (!(envi[i] = (char *)malloc(sizeof(char *) * ft_strlen(env[i]) + 1)))
			return (0);
		ft_strlcpy(envi[i], env[i], ft_strlen(env[i]) + 1);
		i++;
	}
	envi[i] = NULL;
	i = 0;
	while (envi[i])
	{
		printf("%s\n", envi[i]);
		i++;
	}
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

/**int					ft_access(char *path, char *cmd)
{
	DIR* rep;
	struct dirent* fichier_lu;

	rep = NULL;
	rep = opendir(path);
	if (rep == NULL)
		exit(1);
	while ((fichier_lu = readdir(rep)) != NULL)
		if (ft_strcmp(fichier_lu, cmd) == 0)
		{
			if (closedir(rep) == -1)
				exit(-1);
			return (0);
		}
		if (closedir(rep) == -1)
			exit(-1);
		return (-1);
}**/

int ft_access(char *bin)
{
	int fd;

	fd = open(bin, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (0);
}

static void get_path(char **cmd, char **env)
{
	char	*path;
	char	*bin;
	char	**split_path;
	int 	i;

	path = ft_strdup(my_getenv(env, "PATH"));
	bin = NULL;
	split_path = NULL;
	if (path == NULL)
		path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
	if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) != 0)
	{
		split_path = ft_split(path, ':');
		free(path);
		path = NULL;
		i = 0;
		while (split_path[i])
		{
			bin = (char *)ft_calloc(sizeof(char), ft_strlen(split_path[i]) + 1 * ft_strlen(cmd[0]) + 1);
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
		free(cmd[0]);
		cmd[0] = bin;
	}
	else
	{
		free(bin);
		bin = NULL;
	}
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
			perror(cmd[0]);
		exit(EXIT_FAILURE);
	}
}

int			main(int ac, char **av, char **env)
{
	char	*line;
	char	**commande;

	(void)ac;
	(void)av;
	line = NULL;
	while (42)
	{
		write(1, "$alilin> ", 9);
		get_next_line(0, &line);
		commande = ft_split(line, ' ');
		get_path(commande, env);
		free(line);
		if (ft_strncmp(commande[0], "exit()", 7) == 0)
			break ;
		if (commande == NULL)
			write(1, "command not found", 17);
		else
			cmd_execution(commande);
		ft_splitdel(&commande);
	}
	system("leaks minishell");
	return (0);
}
