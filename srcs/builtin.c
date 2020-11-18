/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:27:24 by grigo             #+#    #+#             */
/*   Updated: 2020/11/18 15:01:10 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(char **cmd)
{
	int		i;
	int		arg;

	arg = 0;
	i = 1;
	if (cmd[1] == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (ft_strcmparg(cmd[i]))
		i++;
	if (i != 1)
		arg = 1;
	while (cmd[i])
	{
		ft_putstr(cmd[i]);
		if (cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (arg != 1)
		write(1, "\n", 1);
	return (0);
}

char	**ft_creatpwd(char **env, char *pwd, char *start)
{
	char	**newpwd;

	if (!(newpwd = (char **)malloc(sizeof(char *) * 2)))
		return (NULL);
	if (!(newpwd[0] = (char *)malloc(sizeof(char) *
			(ft_strlen(pwd) + ft_strlen(start) + 1))))
		return (NULL);
	ft_strcpy(newpwd[0], start);
	ft_strcat(newpwd[0], pwd);
	newpwd[1] = NULL;
	env = ft_export(newpwd, env, 0);
	ft_splitdel(&newpwd);
	return (env);
}

char	**ft_newpwd(char **env)
{
	int		i;
	char	*newpwd;

	if (!(newpwd = (char *)malloc(sizeof(char) * (PATH_MAX + 1))))
		return (NULL);
	getcwd(newpwd, PATH_MAX);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("PWD=", env[i], 4))
		{
			free(env[i]);
			if (!(env[i] = (char *)malloc(sizeof(char) *
					(ft_strlen(newpwd) + 5))))
				return (NULL);
			ft_strcpy(env[i], "PWD=");
			ft_strcat(env[i], newpwd);
			break ;
		}
		i++;
	}
	if (env[i] == NULL)
		env = ft_creatpwd(env, newpwd, "PWD=");
	free(newpwd);
	return (env);
}

char	**ft_oldpwd(char **env, char *oldpwd)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("OLDPWD=", env[i], 7))
		{
			free(env[i]);
			if (!(env[i] = (char *)malloc(sizeof(char) *
					(ft_strlen(oldpwd) + 8))))
				return (NULL);
			ft_strcpy(env[i], "OLDPWD=");
			ft_strcat(env[i], oldpwd);
			break ;
		}
		i++;
	}
	if (env[i] == NULL)
		env = ft_creatpwd(env, oldpwd, "OLDPWD=");
	return (env);
}

int		my_cd(char *path, char ***env)
{
	char	*oldpwd;

	oldpwd = NULL;
	if (path == NULL)
		path = my_getenv(*env, "HOME=");
	if (!(oldpwd = (char *)malloc(sizeof(char) * (PATH_MAX + 1))))
		return (2);
	getcwd(oldpwd, PATH_MAX);
	if (chdir(path) == -1)
	{
		ft_puterror("bash: cd: ", path, ": No such file or directory", 1);
		free(oldpwd);
		return (1);
	}
	*env = ft_newpwd(*env);
	*env = ft_oldpwd(*env, oldpwd);
	free(oldpwd);
	return (0);
}
