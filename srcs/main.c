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

void ft_puterror(char *error, char *arg)
{
	write(1, error, ft_strlen(error));
	write(1, arg, ft_strlen(arg));
	write(1, "\n", 1);
}

int tab_len(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int 	ft_cheakarg(char *str)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == ';')
			nb++;
		i++;
	}
	return (nb);
}

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

void position(char **cmd, char **env)
{
	char *path;

	path = NULL;
	if (cmd[1] != NULL)
		write(1, "pwd: too many arguments\n", 24);
	else
	{
		if (!(path = malloc(sizeof(char) * path_max(env))))
			return;
		getcwd(path, path_max(env));
		ft_putstr(path);
		write(1, "\n", 1);
	}
	free(path);
}

void my_cd(char *path, char **env, char **cmd)
{
	char 	*tmp;

	tmp = NULL;
	if (path == NULL)
	{
		tmp = my_getenv(env, "HOME=");
		free(path);
		path = tmp;
	}
	else if (tab_len(cmd) > 3)
	{
		write(1, "cd: too many arguments\n", 23);
		return ;
	}
	else if (tab_len(cmd) == 3)
	{
		ft_puterror("cd: string not in pwd: ", path);
		return ;
	}
	if (chdir(path) == -1 )
		ft_puterror("cd: No such file or directory: ", path);
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
			usable = &env[i][ft_strlen(path)];
			break ;
		}
		i++;
	}
	return (usable);
}

/*void ft_export(char **cmd, char **env)
{
	int i;

	i = 1;
	(void)env;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '=') != NULL && cmd[i][0] != '=')
		{

		}
		if (cmd[i][0] == '=' && ft_strlen(cmd[i]) != 1)
		{
			write(1, "zsh: ", 5);
			write(1, &cmd[i][1], ft_strlen(cmd[i]) - 1);
			write(1, " not found\n", 11);
		}
		if (ft_strlen(cmd[i]) == 1 && ft_strcmp(cmd[i], "=") == 0)
			write(1, "zsh: bad assignment\n", 20);
		i++;
	}
}*/

char 	**ft_export(char **cmd, char **env)
{
	int i;
	int j;
	char **envi;

	i = 1;
	while (cmd[i])
	{
		envi = NULL;
		if (ft_strchr(cmd[i], '=') != NULL && cmd[i][0] != '=')
		{
			j = 0;
			if (!(envi = (char **)malloc(sizeof(env) * tab_len(env) + 2)))
				return NULL;
			while (env[j])
			{
				if (j < tab_len(env) - 1)
				{
					if (!(envi[j] = (char *)malloc(sizeof(char *) * ft_strlen(env[j]) + 1)))
						return NULL;
					ft_strcpy(envi[j], env[j]);
				}
				else
				{
					if (!(envi[j] = (char *)malloc(sizeof(char *) * ft_strlen(cmd[i]) + 1)))
						return NULL;
					ft_strcpy(envi[j], cmd[i]);
				}
				j++;
			}
			if (!(envi[j] = (char *)malloc(sizeof(char *) * ft_strlen(env[j - 1]) + 1)))
				return NULL;
			ft_strcpy(envi[j], env[j - 1]);
			envi[j + 1] = NULL;
		}
		if (envi != NULL)
		{
			j = 0;
			ft_splitdel(&env);
			if (!(env = (char **)malloc(sizeof(env) * tab_len(envi) + 2)))
				return NULL;
			while (envi[j])
			{
				if (!(env[j] = (char *)malloc(sizeof(char) * ft_strlen(envi[j]) + 1)))
					return NULL;
				ft_strcpy(env[j], envi[j]);
				j++;
			}
			env[j] = NULL;
		}
		i++;
	}
	return (env);
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
			ft_puterror("zsh: No such file or directory: ", cmd[0]);
		exit(EXIT_FAILURE);
	}
}

static void exect_built_commande(char **cmd, char ***env)
{
	if (!ft_strcmp(cmd[0], "cd"))
		my_cd(cmd[1], *env, cmd);
	else if (!ft_strcmp(cmd[0], "env"))
		environment(*env);
	else if (!ft_strcmp(cmd[0], "pwd"))
		position(cmd, *env);
	else if (!ft_strcmp(cmd[0], "export"))
		*env = ft_export(cmd, *env);
}

int 				built_command(char *cmd)
{
	char	*build_com[] = {"cd", "env", "pwd", "export", NULL};
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

int                ft_commande(char *line, char ***env)
{
  char    **commande;
	char		**tenv;

	commande = NULL;
	tenv = NULL;
  commande = ft_split(line, ' ');
	if (commande[0] == NULL)
		write(1, "", 0);
	else if (ft_strcmp(commande[0], "exit") == 0)
	{
    ft_splitdel(&commande);
		ft_splitdel(env);
		system("leaks minishell");
		exit(0);
  }
	else if (built_command(commande[0]) == 1)
	{
		exect_built_commande(commande, env);
		//environment(env);
	}
	else
	{
		tenv = ft_getenv(*env);
		if (get_path(commande, tenv) == true)
			cmd_execution(commande);
		else
			ft_puterror("zsh: command not found: ", commande[0]);
		ft_splitdel(&tenv);
		tenv = NULL;
	}
	ft_splitdel(&commande);
	return (1);
}

int 				ft_precommande(char *line, char ***env)
{
	int nbarg;
	char **commande;
	int i;

	commande = NULL;
	nbarg = ft_cheakarg(line);
	if (nbarg == 0)
		ft_commande(line, env);
	else
	{
		commande = ft_split(line, ';');
		i = 0;
		while (commande[i])
		{
			ft_commande(commande[i], env);
			i++;
		}
		ft_splitdel(&commande);
	}
	return (1);
}

int					main(int ac, char **av, char **env)
{
	char	*line;
	char 	**envi;

	(void)ac;
	(void)av;
	line = NULL;
	envi = ft_getenv(env);
	while (1)
	{
		write(1, "$alilin> ", 9);
		get_next_line(0, &line);
    ft_precommande(line, &envi);
		free(line);
		//system("leaks minishell");
	}
	ft_splitdel(&envi);
	envi = NULL;
	system("leaks minishell");
	return (0);
}
