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

int tab_len(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int		my_cd(char *path, char **env)
{
	char 	*tmp;
	char 	*oldpwd;
	char	*newpwd;
	int   i;

	tmp = NULL;
	if (path == NULL)
		path = my_getenv(env, "HOME=");
	if (!(oldpwd = (char *)malloc(sizeof(char) * (PATH_MAX + 1))))
		return (2);
	getcwd(oldpwd, PATH_MAX);
	if (chdir(path) == -1 )
	{
		ft_puterror("bash: cd: ", path, ": No such file or directory\n", 1);
		free(oldpwd);
		return (1);
	}
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("PWD=", env[i], 4))
		{
			free(env[i]);
			if (!(newpwd = (char *)malloc(sizeof(char) * (PATH_MAX + 1))))
				return (2);
			getcwd(newpwd, PATH_MAX);
			if (!(env[i] = (char *)malloc(sizeof(char) * (ft_strlen(newpwd) + 5))))
				return (2);
			ft_strcpy(env[i], "PWD=");
			ft_strcat(env[i], newpwd);
			free(newpwd);
			break ;
		}
		i++;
	}
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("OLDPWD=", env[i], 7))
		{
			free(env[i]);
			if (!(env[i] = (char *)malloc(sizeof(char) * (ft_strlen(oldpwd) + 8))))
				return (2);
			ft_strcpy(env[i], "OLDPWD=");
			ft_strcat(env[i], oldpwd);
			break ;
		}
		i++;
	}
	free(oldpwd);
	return (0);
}

char 	**ft_unset(char **cmd, char **env)
{
	int i;
	int j;
	int idx;
	char **tmp;
	char *tcmd;

	tmp = NULL;
	i = 1;
	errno = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (!ft_isalnum(cmd[i][j]) && cmd[i][j] != '_')
			{
				ft_puterror("bash: unset: `", cmd[i], "': not a valid identifier\n", 1);
				j = -1;
				break ;
			}
			j++;
		}
		if (j != -1)
		{
			if (!(tcmd = (char *)malloc(sizeof(char) * (ft_strlen(cmd[i]) + 2))))
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
				if (!(tmp = (char **)malloc(sizeof(char *) * (tab_len(env)))))
					return (NULL);
				j = 0;
				while(j < idx)
				{
					if (!(tmp[j] = (char *)malloc(sizeof(char) * (ft_strlen(env[j]) + 1))))
						return (NULL);
					ft_strcpy(tmp[j], env[j]);
					j++;
				}
				j++;
				while (j < tab_len(env))
				{
					if (!(tmp[j-1] = (char *)malloc(sizeof(char) * ft_strlen(env[j]) + 1)))
						return (NULL);
					ft_strcpy(tmp[j-1], env[j]);
					j++;
				}
				tmp[j-1] = NULL;
				ft_splitdel(&env);
				if (!(env = (char **)malloc(sizeof(char *) * (tab_len(tmp) + 1))))
					return (NULL);
				j = 0;
				while(tmp[j])
				{
					if (!(env[j] = (char *)malloc(sizeof(char) * (ft_strlen(tmp[j]) + 1))))
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
	char 	**tmp;
	int 	len;

	tmp = NULL;
	i = 1;
	errno = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if ((!ft_isalnum(cmd[i][j]) && cmd[i][j] != '=' && cmd[i][j] != '_')
			|| cmd[i][0] == '=')
			{
				ft_puterror("bash: export: `", cmd[i], "': not a valid identifier\n", 1);
				j = -1;
				break ;
			}
			if (cmd[i][j] == '=')
				break;
			j++;
		}
		if (j != -1)
		{
			if (strchr(cmd[i], '=') != 0 && ft_checkex2(cmd[i], env))
			{
				if (!(tmp = (char **)malloc(sizeof(char *) * (tab_len(env) + 2))))
					return (NULL);
				j = 0;
				while(j < tab_len(env) - 1)
				{
					if (!(tmp[j] = (char *)malloc(sizeof(char) * (ft_strlen(env[j]) + 1))))
						return (NULL);
					ft_strcpy(tmp[j], env[j]);
					j++;
				}
				if (!(tmp[j] = (char *)malloc(sizeof(char) * (ft_strlen(cmd[i]) + 1))))
					return (NULL);
				ft_strcpy(tmp[j], cmd[i]);
				if (!(tmp[j + 1] = (char *)malloc(sizeof(char) * (ft_strlen(env[j]) + 1))))
					return (NULL);
				ft_strcpy(tmp[j + 1], env[j]);
				tmp[j + 2] = NULL;
				ft_splitdel(&env);
				if (!(env = (char **)malloc(sizeof(char *) * (tab_len(tmp) + 1))))
					return (NULL);
				j = 0;
				while (tmp[j])
				{
					if (!(env[j] = (char *)malloc(sizeof(char) * (ft_strlen(tmp[j]) + 1))))
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
				while (cmd[i][j] != '=' && cmd[i][j])
					j++;
				len = j;
				j = 0;
				while (env[j])
				{
					if (ft_strncmp(cmd[i], env[j], len) == 0)
					{
						free(env[j]);
						if (!(env[j] = (char *)malloc(sizeof(char) * (ft_strlen(cmd[i]) + 1))))
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

int 		ft_echo(char **cmd)
{
	int i;
	int j;
	int n = 0;

	if (cmd[1] == NULL)
	{
		write(1, "\n", 1);
		return (0);
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
	return (0);
}

char 								*ft_variables(char *str, int idx, char **env)
{
	int i;
	char *tmp;
	char *str_tmp;
	char *tenv;

	tenv = NULL;
	str_tmp = NULL;
	if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + PATH_MAX + 1))))
		return (NULL);
	if (idx != 0)
		ft_strlcpy(tmp, str, idx + 1);
	idx++;
	if (str[idx] != '?')
	{
		if (!(str_tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
			return (NULL);
		i = 0;
		while(str[idx] && str[idx] != '$' && str[idx] != ' ' && str[idx] != '"')
		{
			str_tmp[i] = str[idx];
			idx++;
			i++;
		}
		str_tmp[i] = '=';
		str_tmp[i + 1] = '\0';
		if ((tenv = my_getenv(env, str_tmp)) != NULL)
			ft_strcat(tmp, tenv);
		tenv = NULL;
		free(str_tmp);
	}
	else
	{
		tenv = ft_itoa(errno);
		ft_strcat(tmp, tenv);
		free(tenv);
		idx++;
	}
	if (str[idx] != '\0')
		ft_strcat(tmp, &str[idx]);
	free(str);
	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 1))))
		return (NULL);
	ft_strcpy(str, tmp);
	free(tmp);
	return (str);
}

char 								*ft_backslash(char *str, int bsl)
{
	char 	*tmp;
	int 	i;

	if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(str)))))
		return (NULL);
	i = 0;
	while (i != bsl)
	{
		tmp[i] = str[i];
		i++;
	}
	bsl++;
	while (str[bsl])
	{
		tmp[i] = str[bsl];
		i++;
		bsl++;
	}
	tmp[i] = '\0';
	free(str);
	if (!(str = (char *)malloc(sizeof(char*) + (ft_strlen(tmp) + 1))))
		return (NULL);
	ft_strcpy(str, tmp);
	free(tmp);
	return (str);
}

char 								*variables1(char *str, char **env)
{
	int 	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		if (str[i] == '$')
		{
			if (ft_strlen(str) != 1 && str[i + 1] != '\0' && str[i + 1] != ' ')
			{
				str = ft_variables(str, i, env);
				i	= -1;
			}
		}
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i])
			{
				if (str[i] == '$')
				{
					if (ft_strlen(str) != 1 && str[i + 1] != '\0' && str[i + 1] != ' ')
						str = ft_variables(str, i, env);
				}
				if (str[i] == '\\' && str[i + 1] == '\\')
					str = ft_backslash(str, i);
				i++;
			}
		}
		if (str[i] == '\\')
			str = ft_backslash(str, i);
		i++;
	}
	return (str);
}

int 								ft_cword(char *line)
{
	int 	i;
	int 	nb;
	char 	sep;

	i = 0;
	nb = 1;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			sep = line[i];
			i++;
			while (line[i] != sep && line[i])
				i++;
		}
		if (line[i] == ' ')
		{
			while (line[i + 1] == ' ')
				i++;
			nb++;
		}
		i++;
	}
	return (nb);
}

int  								ft_sepcount(char *line, char c)
{
	int len;

	len = 0;
	while (line[len] != c)
		len++;
	return (len + 1);
}

char 									**creat_list_arg(char *line)
{
	char	**commande;
	int 	i;
	int 	j;
	int 	first;

	if (!(commande = (char **)malloc(sizeof(char *) * (ft_cword(line) + 1))))
		return (NULL);
	i = 0;
	first = 0;
	j = 0;
	if (!(commande[j] = (char *)ft_calloc(sizeof(char), (ft_strlen(line) + 1))))
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (i != first)
			{
				commande[j] = ft_strncat(commande[j], &line[first], i - first);
				i++;
				first = i;
				commande[j] = ft_strncat(commande[j], &line[first], ft_sepcount(&line[first], line[i - 1]) - 1);
				i += ft_sepcount(&line[first], line[i - 1]);
				first = i;
				i--;
			}
			else
			{
				i++;
				commande[j] = ft_strncat(commande[j], &line[i], ft_sepcount(&line[i], line[i - 1]) - 1);
				i += ft_sepcount(&line[i], line[i - 1]);
				first = i;
				i--;
			}
		}
		if (line[i] == ' ')
		{
			if (line[i + 1] == '\0')
				break ;
			commande[j] = ft_strncat(commande[j], &line[first], i - first);
			while (line[i + 1] == ' ')
				i++;
			first = i + 1;
			j++;
			if (line[i + 1] != '\0')
				if (!(commande[j] = (char *)ft_calloc(sizeof(char), (ft_strlen(line) + 1))))
					return (NULL);
		}
		i++;
	}
	if (first != i)
	{
		commande[j] = ft_strncat(commande[j], &line[first], i - first);
		commande[j + 1] = NULL;
	}
	else
		commande[j + 1] = NULL;
	return (commande);
}

char  *my_redirection(char *str)
{
	if (ft_strchr(str, '>') || ft_strchr(str, '<'))
		str = ft_checkredir(str);
	return (str);
}

char 		**my_redir_right(char **cmd, int idx, int f_open[2])
{
	int 	i;
	int 	j;
	char 	**tmp;

	i = 0;
	tmp = NULL;
	if (!ft_strcmp(cmd[idx], ">"))
	{
		if (f_open[0] == 1)
			close(g_file[0]);
		if ((g_file[0] = open(cmd[idx + 1], O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			write(2, "error: open failed\n", 19);
		else
			f_open[0] = 1;
	}
	else if (!ft_strcmp(cmd[idx], ">>"))
	{
		if (f_open[0])
			close(g_file[0]);
		if ((g_file[0] = open(cmd[idx + 1], O_CREAT | O_WRONLY | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			write(2, "error: open failed\n", 19);
		else
			f_open[0] = 1;
	}
	if (!(tmp = (char **)malloc(sizeof(char *) * (tab_len(cmd) - 2 + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (i != idx && i != idx + 1)
		{
			if (!(tmp[j] = (char *)malloc(sizeof(char) * (ft_strlen(cmd[i]) + 1))))
				return (NULL);
			ft_strcpy(tmp[j], cmd[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	ft_splitdel(&cmd);
	if (!(cmd = (char **)malloc(sizeof(char*) * (tab_len(tmp) + 1))))
		return (NULL);
	i = 0;
	while(tmp[i])
	{
		if (!(cmd[i] = (char *)malloc(sizeof(char) * (ft_strlen(tmp[i]) + 1))))
			return (NULL);
		ft_strcpy(cmd[i], tmp[i]);
		i++;
	}
	cmd[i] = NULL;
	ft_splitdel(&tmp);
	if (i == 0)
	{
		ft_splitdel(&cmd);
		return (NULL);
	}
	return (cmd);
}

char 		**my_redir_left(char **cmd, int idx, int f_open[2])
{
	int	i;
	int	j;
	char **tmp;

	if (f_open[1])
		close(g_file[1]);
	if ((g_file[1] = open(cmd[idx + 1], O_RDONLY)) == -1)
	{
		ft_puterror("bash: ", cmd[idx + 1], ": No such file or directory\n", errno);
		ft_splitdel(&cmd);
		return NULL;
	}
	f_open[1] = 1;
	if (!(tmp = (char **)malloc(sizeof(char *) * (tab_len(cmd) - 2 + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (i != idx && i != idx + 1)
		{
			if (!(tmp[j] = (char *)malloc(sizeof(char) * (ft_strlen(cmd[i]) + 1))))
				return (NULL);
			ft_strcpy(tmp[j], cmd[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	ft_splitdel(&cmd);
	if (!(cmd = (char **)malloc(sizeof(char*) * (tab_len(tmp) + 1))))
		return (NULL);
	i = 0;
	while(tmp[i])
	{
		if (!(cmd[i] = (char *)malloc(sizeof(char) * (ft_strlen(tmp[i]) + 1))))
			return (NULL);
		ft_strcpy(cmd[i], tmp[i]);
		i++;
	}
	cmd[i] = NULL;
	ft_splitdel(&tmp);
	if (cmd[0] == NULL)
	{
		ft_splitdel(&cmd);
		return (NULL);
	}
	return (cmd);
}

char 		**detectcmd(char **cmd)
{
	int i;
	int f_open[2];

	i = 0;
	g_cvr[0] = 0;
	g_cvr[1] = 0;
	g_file[0] = 0;
	g_file[1] = 0;
	f_open[0] = 0;
	f_open[1] = 0;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], ">") || !ft_strcmp(cmd[i], ">>"))
		{
			if (!(cmd = my_redir_right(cmd, i, f_open)))
				return (NULL);
			g_cvr[0] = 1;
			f_open[0] = 1;
			i--;
		}
		if (!ft_strcmp(cmd[i], "<"))
		{
			if (!(cmd = my_redir_left(cmd, i, f_open)))
				return (NULL);
			g_cvr[1] = 1;
			f_open[1] = 1;
			i--;
		}
		if (cmd[i][0] == 1 && cmd[i][1] == '\0')
			cmd[i][0] = '>';
		if (cmd[i][0] == 1 && cmd[i][1] == 1 && cmd[i][2] == '\0')
		{
			cmd[i][0] = '>';
			cmd[i][1] = '>';
		}
		if (cmd[i][0] == 2 && cmd[i][1] == '\0')
			cmd[i][0] = '<';
		i++;
	}
	if (g_cvr[0])
	{
		g_fd[0] = dup(STDOUT_FILENO);
		close(STDOUT_FILENO);
		if (dup2(g_file[0], STDOUT_FILENO) == -1)
			write(2, "error: dup2 failed\n", 19);
	}
	if (g_cvr[1])
	{
		g_fd[1] = dup(0);
		close(0);
		if (dup2(g_file[1], 0) == -1)
			write(2, "error: dup2 failed\n", 19);
	}
	return (cmd);
}

void	cmd_execution(char **cmd)
{
	int			status;

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

void ft_pute() {
	write(1, "\033[1;37mPourquoi tu es mechant :/\n\033[0;37m", 40);
}

void ft_grosse_merde(){
	write(1, "\033[0;31mtoi même connard !\033[0;37m\n", 34);
}

void exect_built_commande(char **cmd, char ***env)
{
	if (!ft_strcmp(cmd[0], "cd"))
		errno = my_cd(cmd[1], *env);
	else if (!ft_strcmp(cmd[0], "env"))
		errno = environment(cmd, *env);
	else if (!ft_strcmp(cmd[0], "pwd"))
		errno = position();
	else if (!ft_strcmp(cmd[0], "export"))
		*env = ft_export(cmd, *env);
	else if (!ft_strcmp(cmd[0], "unset"))
		*env = ft_unset(cmd, *env);
	else if (!ft_strcmp(cmd[0], "echo"))
		errno = ft_echo(cmd);
	else if (!ft_strcmp(cmd[0], "pute"))
		ft_pute();
	else if (!ft_strcmp(cmd[0], "grosse_merde"))
		ft_grosse_merde();
}

int 				built_command(char *cmd)
{
	char *build_com[9];
	int 	i;

	build_com[0] = "cd";
	build_com[1] = "env";
	build_com[2] = "pwd";
	build_com[3] = "export";
	build_com[4] = "unset";
	build_com[5] = "echo";
	build_com[6] = "pute";
	build_com[7] = "grosse_merde";
	build_com[8] = NULL;
	i = 0;
	while (build_com[i])
	{
		if (ft_strcmp(build_com[i], cmd) == 0)
			return (1);
		i++;
	}
	return (0);
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
	signal(SIGQUIT, end);
	while (1)
	{
		write(1, "\033[1;34m$alilin> \033[0;37m", 23);
		if (get_next_line(0, &line) == 0)
			ft_exit(NULL);
    ft_precommande(line, &envi);
		free(line);
		line = NULL;
	}
	return (0);
}
