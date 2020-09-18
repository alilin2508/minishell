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

int 	ft_checkexport(char **cmd)
{
	int i;

	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] == '=' && ft_strlen(cmd[i]) > 1)
			return (i);
		i++;
	}
	return (0);
}

int 	ft_checkex2(char *cmd, char **env)
{
	int i;
	int len;

	i = 0;
	while (cmd[i] != '=')
		i++;
	len = i;

	while (env[i])
	{
		if (ft_strncmp(cmd, env[i], len) == 0)
			return (0);
		i++;
	}
	return (1);
}

int 	ft_checkunset(char *cmd, char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], cmd, ft_strlen(cmd)))
			return (i + 1);
		i++;
	}
	return (0);
}

char 	**ft_unset(char **cmd, char **env)
{
	int i;
	int error;
	int j;
	int idx;
	char **tmp;
	char *tcmd;

	tmp = NULL;
	if ((error = ft_checkexport(cmd)) != 0)
	{
		write(1, "zsh: ", 5);
		write(1, &cmd[error][1], ft_strlen(cmd[error]) - 1);
		write(1, " not found\n", 11);
		return (env);
	}
	i = 1;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (!ft_isalnum(cmd[i][j]))
			{
				write(1, "unset: ", 7);
				write(1, cmd[i], ft_strlen(cmd[i]));
				write(1, ": invalid parameter name\n", 25);
				j = -1;
				break ;
			}
			j++;
		}
		if (j != -1)
		{
			if (!(tcmd = (char *)malloc(sizeof(char *) * (ft_strlen(cmd[i]) + 2))))
				return (NULL);
			j = 0;
			while (cmd[i][j])
			{
				tcmd[j] = cmd[i][j];
				j++;
			}
			tcmd[j] = '=';
			tcmd[j + 1] = '\0';
			if ((idx = ft_checkunset(tcmd, env) - 1) != -1)
			{
				if (!(tmp = (char **)malloc(sizeof(char **) * (tab_len(env)))))
					return (NULL);
				j = 0;
				while(j < idx)
				{
					if (!(tmp[j] = (char *)malloc(sizeof(char *) * (ft_strlen(env[j]) + 1))))
						return (NULL);
					ft_strcpy(tmp[j], env[j]);
					j++;
				}
				j++;
				while (j < tab_len(env))
				{
					if (!(tmp[j-1] = (char *)malloc(sizeof(char*) * ft_strlen(env[j]) + 1)))
						return (NULL);
					ft_strcpy(tmp[j-1], env[j]);
					j++;
				}
				tmp[j-1] = NULL;
				ft_splitdel(&env);
				if (!(env = (char **)malloc(sizeof(char **) * (tab_len(tmp) + 1))))
					return (NULL);
				j = 0;
				while(tmp[j])
				{
					if (!(env[j] = (char *)malloc(sizeof(char *) * (ft_strlen(tmp[j]) + 1))))
						return (NULL);
					ft_strcpy(env[j], tmp[j]);
					j++;
				}
				env[j] = NULL;
				ft_splitdel(&tmp);
				tmp = NULL;
			}
			free(tcmd);
		}
		i++;
	}
	return (env);
}

char 	**ft_export(char **cmd, char **env)
{
	int 	i;
	int 	j;
	int 	error;
	char 	**tmp;
	int 	len;

	tmp = NULL;
	if ((error = ft_checkexport(cmd)) != 0)
	{
		write(1, "zsh: ", 5);
		write(1, &cmd[error][1], ft_strlen(cmd[error]) - 1);
		write(1, " not found\n", 11);
		return (env);
	}
	i = 1;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (!ft_isalnum(cmd[i][j]) && cmd[i][j] != '=')
			{
				write(1, "export: not valid in this context: ", 35);
				j = 0;
				while (cmd[i][j] != '=' && cmd[i][j])
				{
					write(1, &cmd[i][j], 1);
					j++;
				}
				write(1, "\n", 1);
				j = -1;
				break ;
			}
			j++;
		}
		if (j != -1)
		{
			if (cmd[i][0] == '=')
			{
				if (ft_strlen(cmd[i]) == 1 && i == 1)
					write(1, "zsh: bad assignment\n", 20);
				else if (ft_strlen(cmd[i]) == 1 && i != 1)
					write(1, "export: not valid in this context:\n", 35);
				break ;
			}
			if (strchr(cmd[i], '=') != 0 && ft_checkex2(cmd[i], env))
			{
				if (!(tmp = (char **)malloc(sizeof(char **) * (tab_len(env) + 2))))
					return (NULL);
				j = 0;
				while(j < tab_len(env) - 1)
				{
					if (!(tmp[j] = (char *)malloc(sizeof(char *) * (ft_strlen(env[j]) + 1))))
						return (NULL);
					ft_strcpy(tmp[j], env[j]);
					j++;
				}
				if (!(tmp[j] = (char *)malloc(sizeof(char *) * (ft_strlen(cmd[i]) + 1))))
					return (NULL);
				ft_strcpy(tmp[j], cmd[i]);
				if (!(tmp[j + 1] = (char *)malloc(sizeof(char *) * (ft_strlen(env[j]) + 1))))
					return (NULL);
				ft_strcpy(tmp[j + 1], env[j]);
				tmp[j + 2] = NULL;
				ft_splitdel(&env);
				if (!(env = (char **)malloc(sizeof(char **) * (tab_len(tmp) + 1))))
					return (NULL);
				j = 0;
				while (tmp[j])
				{
					if (!(env[j] = (char *)malloc(sizeof(char *) * (ft_strlen(tmp[j]) + 1))))
						return (NULL);
					ft_strcpy(env[j], tmp[j]);
					j++;
				}
				env[j] = NULL;
				ft_splitdel(&tmp);
				tmp = NULL;
			}
			else
			{
				j = 0;
				while (cmd[i][j] != '=')
					j++;
				len = j;
				j = 0;
				while (env[j])
				{
					if (ft_strncmp(cmd[i], env[j], len) == 0)
					{
						free(env[j]);
						if (!(env[j] = (char *)malloc(sizeof(char *) * (ft_strlen(cmd[i]) + 1))))
							return (NULL);
						ft_strcpy(env[j], cmd[i]);
						break ;
					}
					j++;
				}
			}
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

void 		ft_echo(char **cmd)
{
	int i;
	int j;
	int n = 0;

	if (cmd[1] == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	if (!ft_strcmp(cmd[1], "-n"))
		n = 1;
	if (n == 0)
		i = 1;
	else
		i = 2;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			write(1, &cmd[i][j], 1);
			j++;
		}
		if (cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (n == 0)
		write(1, "\n",  1);
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
	else if (!ft_strcmp(cmd[0], "unset"))
		*env = ft_unset(cmd, *env);
	else if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(cmd);
}

int 				built_command(char *cmd)
{
	char	*build_com[] = {"cd", "env", "pwd", "export", "unset", "echo", NULL};
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
		write(1, "TROP BIEN CE SHELL\n", 19);
		system("leaks minishell");
		exit(0);
  }
	else if (built_command(commande[0]) == 1)
		exect_built_commande(commande, env);
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

void 				end()
{

	exit(0);
}

void 				recovery(int sig)
{
	switch(sig){
		case SIGINT:
			write(1, "\n$alilin> ", 10);
	}
}

int					main(int ac, char **av, char **env)
{
	char	*line;
	char 	**envi;

	(void)ac;
	(void)av;
	line = NULL;
	envi = ft_getenv(env);
	signal(SIGINT, recovery);
	signal(EOF, recovery);
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
