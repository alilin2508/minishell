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

pid_t pid;
char 	*mess;

void ft_puterror(char *errorstart, char *arg, char *errorend)
{
	write(2, errorstart, ft_strlen(errorstart));
	write(2, arg, ft_strlen(arg));
	write(2, errorend, ft_strlen(errorend));
}

int 		parse_error(int t_e)
{
	if (t_e == 1)
		write(2, "bash: syntax error near unexpected token `;;'\n", 46);

	return(t_e);
}

int tab_len(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int 		ft_checkerror(const char *str)
{
	int 	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ';' && str[i + 1] == ';')
			return (parse_error(1));
		//if ()
		i++;
	}
	return (0);
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
	errno = 0;
}

void position(char **env)
{
	char *path;

	path = NULL;
	(void )env;
	if (!(path = (char*)malloc(sizeof(char) * PATH_MAX)))
		return;
	getcwd(path, PATH_MAX);
	ft_putstr(path);
	write(1, "\n", 1);
	free(path);
	errno = 0;
}

void my_cd(char *path, char **env)
{
	char 	*tmp;
	char 	*oldpwd;
	char	*newpwd;
	int   i;

	tmp = NULL;
	if (path == NULL)
		path = my_getenv(env, "HOME=");
	if (!(oldpwd = (char *)malloc(sizeof(char) * (PATH_MAX + 1))))
		return ;
	getcwd(oldpwd, PATH_MAX);
	if (chdir(path) == -1 )
	{
		ft_puterror("bash: cd: ", path, ": No such file or directory\n");
		free(oldpwd);
		return ;
	}
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("PWD=", env[i], 4))
		{
			free(env[i]);
			if (!(newpwd = (char *)malloc(sizeof(char) * (PATH_MAX + 1))))
				return ;
			getcwd(newpwd, PATH_MAX);
			if (!(env[i] = (char *)malloc(sizeof(char) * (ft_strlen(newpwd) + 5))))
				return ;
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
				return ;
			ft_strcpy(env[i], "OLDPWD=");
			ft_strcat(env[i], oldpwd);
			free(oldpwd);
			break ;
		}
		i++;
	}

	errno = 0;
}

char **ft_getenv(char **env)
{
	char 	**envi;
	int 	i;

	i = 0;
	while (env[i])
		i++;
	if (!(envi = (char**)malloc(sizeof(char *) * i + 1)))
		return (0);
	i = 0;
	while (env[i])
	{
		if (!(envi[i] = (char *)malloc(sizeof(char) * ft_strlen(env[i]) + 1)))
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
	int j;
	int idx;
	char **tmp;
	char *tcmd;

	tmp = NULL;
	i = 1;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (!ft_isalnum(cmd[i][j]) && cmd[i][j] != '_')
			{
				ft_puterror("bash: unset: `", cmd[i], "': not a valid identifier\n");
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
	int 	error;
	char 	**tmp;
	int 	len;

	tmp = NULL;
	i = 1;
	while (cmd[i])
	{
		j = 0;
		error = 0;
		while (cmd[i][j])
		{
			if ((!ft_isalnum(cmd[i][j]) && cmd[i][j] != '=' && cmd[i][j] != '_')
			|| cmd[i][0] == '=')
			{
				ft_puterror("bash: export: `", cmd[i], "': not a valid identifier\n");
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
			if (!ft_strncmp(env[i], "PATH=", 5)) {
				path = ft_strdup(&env[i][5]);
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
	errno = 0;
}

char 								*ft_variables(char *str, int idx, char **env)
{
	int i;
	char *tmp;
	char *str_tmp;
	char *tenv;

	tenv = NULL;
	if (!(str_tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2))))
		return (NULL);
	if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + PATH_MAX))))
		return (NULL);
	if (idx != 0)
		ft_strlcpy(tmp, str, idx + 1);
	idx++;
	if (str[idx] != '?')
	{
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
	ft_strcpy(str, tmp);
	free(tmp);
	free(str_tmp);
	errno = 0;
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
	ft_strcpy(str, tmp);
	free(tmp);
	return (str);
}

char 								*variables$(char *str, char **env)
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
				ft_variables(str, i, env);
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
					{
						ft_variables(str, i, env);
						i	= -1;
					}
				}
				if (str[i] == '\\' && str[i + 1] == '\\')
					ft_backslash(str, i);
				i++;
			}
		}
		if (str[i] == '\\')
			ft_backslash(str, i);
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
	while (i < ft_cword(line) + 1)
	{
		commande[i] = NULL;
		i++;
	}
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

int 		ft_nb_cmd(const char *line)
{
	int 	i;
	int 	nb;
	char 	c;

	i = 0;
	nb = 1;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			c = line[i];
			i++;
			while (line[i] && line[i] != c)
				i++;
			if (line[i] == '\0')
				return (-1);
		}
		if (line[i] == ';')
			nb++;
		if (line[i] == '\\')
			i++;
		i++;
	}
	return (nb);
}

char 		*ft_takecmd(char *str, int first, int last)
{
	int 	i;
	char 	*s;

	while (str[first] == ';' || str[first] == ' ')
		first++;
	if (str[first] == '\0')
		return (NULL);
	if (!(s = (char *)malloc(sizeof(char) * (last - first + 2))))
		return (NULL);
	i = 0;
	while (first < last)
	{
		s[i] = str[first];
		i++;
		first++;
	}
	s[i] = '\0';
	return (s);
}

char 		**ft_splitcmd(char *str)
{
	char 	**tab;
	int	 	first;
	int 	i;
	int 	j;
	char 	c;

	if (ft_nb_cmd(str) == -1)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char*) * (ft_nb_cmd(str) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	first = 0;
	while (str[j])
	{
		if (str[j] == '"' || str[j] == '\'')
		{
			c = str[j];
			j++;
			while (str[j] && str[j] != c)
				j++;
		}
		if (str[j] == ';')
		{
			if ((tab[i] = ft_takecmd(str, first, j)) == NULL)
			{
				i++;
				tab[i] = NULL;
				i = -1;
				break ;
			}
			i++;
			j++;
			while (str[j] == ' ' && str[j] == ';')
				j++;
			first = j;
		}
		if (str[j] == '\\')
			j++;
		j++;
	}
	if (i != -1)
	{
		tab[i] = ft_takecmd(str, first, j);
		tab[i + 1] = NULL;
	}
	return (tab);
}

int 								ft_nbchevron(char *str)
{
	int 	i;
	int 	nb;
	char 	c;

	i = 0;
	nb= 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i])
				i++;
		}
		if ((str[i - 1] != '>' && str[i] == '>' && str[i + 1] != '>'
		&& (str[i + 1] != ' ' || str[i - 1] != ' '))
		|| (str[i] == '>' && str[i + 1] == '>' &&
		(str[i + 2] != ' ' || str[i - 1] != ' '))
		|| (str[i] == '<' && (str[i - 1] != ' ' || str[i + 1] != ' ')))
			nb++;
		i++;
	}
	return (nb);
}

void 								ft_chevronspace(char *str)
{
	char 		*tmp;
	int 		i;
	int 		j;
	char		c;

	if (!(tmp = (char *)malloc(sizeof(char) *
	(ft_strlen(str) + ft_nbchevron(str) * 2 + 1))))
		return ;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i])
				i++;
		}
		if (((str[i] == '>' && str[i - 1] != ' ' && str[i - 1] != '>')
		|| (str[i] == '<' && str[i - 1] != ' ')) && i != 0)
		{
			tmp[j] = ' ';
			j++;
		}
		else if ((str[i - 1] == '>' && str[i] != ' ' && str[i] != '>')
		|| (str[i - 1] == '<' && str[i] != ' '))
		{
			tmp[j] = ' ';
			j++;
		}
		tmp[j] = str[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	ft_strcpy(str, tmp);
	free(tmp);
}

void ft_checkredir(char *str)
{
	int 	i;
	char 	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i])
				i++;
		}
		if ((str[i - 1] != '>' && str[i] == '>' && str[i + 1] != '>'
		&& (str[i + 1] != ' ' || str[i - 1] != ' '))
		|| (str[i] == '>' && str[i + 1] == '>'
		&& (str[i + 2] != ' ' || str[i - 1] != ' '))
		|| (str[i] == '<' && (str[i - 1] != ' ' || str[i + 1] != ' ')))
			ft_chevronspace(str);
		i++;
	}
}

int 		ft_nbpipe(const char *str)
{
	int i;
	int nb;
	char c;

	i = 0;
	nb = 0;
	while(str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i];
			i++;
			while(str[i] != c && str[i])
				i++;
		}
		if (str[i] == '|' && (str[i - 1] != ' ' || str[i + 1] != ' '))
			nb++;
		i++;
	}
	return(nb);
}

void 		ft_pipespace(char *str)
{
		char 	*tmp;
		int 	i;
		int 	j;
		char 	c;


		if (!(tmp = (char *)malloc(sizeof(char) *
		(ft_strlen(str) + ft_nbpipe((const char *)str) * 2 + 1))))
			return ;
		i = 0;
		j = 0;
		while (str[i])
		{
			if (str[i] == '"' || str[i] =='\'')
			{
				c = str[i];
				i++;
				while (str[i] == c && str[i])
					i++;
			}
			if (str[i] == '|' && str[i - 1] != ' ')
			{
				tmp[j] = ' ';
				j++;
			}
			else if (str[i - 1] == '|' && str[i] != ' ')
			{
				tmp[j] = ' ';
				j++;
			}
			tmp[j] = str[i];
			j++;
			i++;
		}
		tmp[j] = '\0';
		ft_strcpy(str, tmp);
		free(tmp);
}

void 		ft_checkpipe(char *str)
{
	int 	i;
	char 	c;

	i = 0;
	while(str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i])
				i++;
		}
		if (str[i] == '|' && (str[i - 1] != ' ' || str[i + 1] != ' '))
			ft_pipespace(str);
		i++;
	}
}

void my_redirection(char *str)
{
	if (ft_strchr(str, '>') || ft_strchr(str, '<'))
		ft_checkredir(str);
	if (ft_strchr(str, '|'))
		ft_checkpipe(str);
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
		ft_puterror("bash: ", cmd[idx + 1], ": No such file or directory\n");
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

void 		my_pipe(char *cmd, char ***env)
{
	int 		pid;
	int 		pfd[2];
	int 		status;

	if (pipe(pfd) == -1)
	{
		write(2, "pipe failed\n", 12);
		return ;
	}
	if ((pid = fork()) == -1)
		write(2, "fork failed\n", 12);
	if (pid == 0)
		{
			close(pfd[1]);
			dup2(pfd[0], 0);
			close(pfd[0]);
			if (ft_strlen("ok") == 2)
				waitpid(0, &status, WNOHANG);
			else
				waitpid(pid, &status, WSTOPPED);
		}
	else
		{
			close(pfd[0]);
			dup2(pfd[1], 1);
			close(pfd[1]);
		}
	ft_commande(cmd, env);
}

void 		soon_pipe(int pfd[2])
{


	close(pfd[1]);
	dup2(pfd[0], 0);
	close(pfd[0]);
	execlp("wc", "wc", (char *)0);
	write(2, "NULL\n", 5);
}

void  	father_pipe(int pfd[2])
{
	close(pfd[0]);
	dup2(pfd[1], 1);
	close(pfd[1]);
	execlp("ls", "ls", (char *)0);
	write(2, "NULL\n", 5);
}

static void	cmd_execution(char **cmd)
{
	int		status;

	pid = 0;
	status = 0;
	pid = fork();
	if (pid == -1)
		write(2, "fork fail\n", 10);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
		errno = 0;
	}
	else
	{
		if (execve(cmd[0], cmd, NULL) == -1)
		{
			ft_puterror("bash: ", cmd[0], ": command not found\n");
			errno = 1;
		}
		exit(EXIT_FAILURE);
	}
}

void ft_pute() {
	write(1, "\033[1;37mPourquoi tu es mechant :/\n\033[0;37m", 40);
}

void ft_grosse_merde(){
	write(1, "\033[0;31mtoi même connard !\033[0;37m\n", 34);
}

static void exect_built_commande(char **cmd, char ***env)
{
	if (!ft_strcmp(cmd[0], "cd"))
		my_cd(cmd[1], *env);
	else if (!ft_strcmp(cmd[0], "env"))
		environment(*env);
	else if (!ft_strcmp(cmd[0], "pwd"))
		position(*env);
	else if (!ft_strcmp(cmd[0], "export"))
		*env = ft_export(cmd, *env);
	else if (!ft_strcmp(cmd[0], "unset"))
		*env = ft_unset(cmd, *env);
	else if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd[0], "pute"))
		ft_pute();
	else if (!ft_strcmp(cmd[0], "grosse_merde"))
		ft_grosse_merde();
}

int 				built_command(char *cmd)
{
	char	*build_com[] = {"cd", "env", "pwd", "export", "unset", "echo", "pute", "grosse_merde", NULL};
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

int 								ft_exit(char **commande)
{
	int ex;

	ex = 0;
	if (commande != NULL)
	{
		if (commande[1] != NULL && ft_isdigit(commande[1][0]))
		{
			ex = ft_atoi(commande[1]);
		}
		ft_splitdel(&commande);
		write(1, "TROP BIEN CE SHELL\n", 19);
		system("leaks minishell");
		exit(ex);
	}
	exit(ex);
}

int                	ft_commande(char *line, char ***env)
{
  char    **commande;
	char		**tenv;

	commande = NULL;
	tenv = NULL;
	if ((variables$(line, *env)) == NULL)
		return (0);
	if ((commande = creat_list_arg(line)) == NULL)
		return (0);
	commande = detectcmd(commande);
	if (commande == NULL)
		write(1, "", 0);
	else if (ft_strcmp(commande[0], "exit") == 0)
		ft_exit(commande);
	else if (built_command(commande[0]))
		exect_built_commande(commande, env);
	else
	{
		tenv = ft_getenv(*env);
		if (get_path(commande, tenv) == true)
			cmd_execution(commande);
		else
		{
			ft_puterror("bash: ", commande[0], ": command not found\n");
			errno = 127;
		}
		ft_splitdel(&tenv);
		tenv = NULL;
	}
	if (commande)
		ft_splitdel(&commande);
	if (g_fd[0] != 0 && g_cvr[0])
	{
		close(STDOUT_FILENO);
		if (dup2(g_fd[0], STDOUT_FILENO) == -1)
			write(2, "error: dup2 failed\n", 19);
		close(g_file[0]);
		close(g_fd[0]);
		g_fd[0] = 0;
	}
	if (g_fd[1] != 0 && g_cvr[1])
	{
		close(0);
		if (dup2(g_fd[1], 0) == -1)
			write(2, "error: dup2 failed\n", 19);
		close(g_file[1]);
		close(g_fd[1]);
		g_fd[1] = 0;
	}
	return (1);
}

int 				ft_precommande(char *line, char ***env)
{
	char **commande;
	int i;

	commande = NULL;
	if (ft_checkerror(line))
		return (0);
	while (line[0] == ' ' || line[0] == ';')
		line += 1;
	if ((commande = ft_splitcmd(line)) == NULL)
	{
		write(2, "bash: error: missing quote\n", 27);
		return (0);
	}
	i = 0;
	while (commande[i])
	{
		//my_pipe(commande[i], env);
		my_redirection(commande[i]);
		ft_commande(commande[i], env);
		i++;
	}
	ft_splitdel(&commande);
	return (1);
}

void 				end(int sig)
{
	(void)sig;

	if (pid != 0)
	{
		write(2, "Quit: 3\n", 8);
		kill(pid, SIGQUIT);
	}
	else
		ft_putstr("\b \b\b \b");
}

void 				recovery(int sig)
{
	(void)sig;
	if (pid == 0)
	{
		ft_putstr("\b \b\b \b\n");
		write(1, "\033[1;34m$alilin> \033[0;37m", 23);
	}
	else
	{
		kill(pid, SIGINT);
		write(1, "\n", 1);
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
	signal(SIGQUIT, end);
	while (1)
	{
		write(1, "\033[1;34m$alilin> \033[0;37m", 23);
		if (get_next_line(0, &line) == 0)
			ft_exit(NULL);
		mess = line;
		if (ft_strcmp(line, "\0") != 0)
    	ft_precommande(line, &envi);
		pid = 0;
		mess = NULL;
		free(line);
		line = NULL;
	}
	return (0);
}
