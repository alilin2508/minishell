/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:27:34 by grigo             #+#    #+#             */
/*   Updated: 2020/11/12 14:58:28 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_getenv(char **env)
{
	char	**envi;
	int		i;

	if (!(envi = (char**)malloc(sizeof(char *) * (tab_len(env) + 1))))
		return (0);
	i = 0;
	while (env[i])
	{
		if (!(envi[i] = (char *)malloc(sizeof(char) * (ft_strlen(env[i]) + 1))))
			return (0);
		ft_strlcpy(envi[i], env[i], ft_strlen(env[i]) + 1);
		i++;
	}
	envi[i] = NULL;
	return (envi);
}

char	*my_getenv(char **env, char *path)
{
	int		i;
	char	*usable;

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

int		environment(char **cmd, char **env)
{
	int		i;

	i = 0;
	if (cmd[1] != NULL)
	{
		write(1, "bash: to many arguments\n", 24);
		return (127);
	}
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			ft_putstr(env[i]);
			write(1, "\n", 1);
		}
		i++;
	}
	return (0);
}

int		position(void)
{
	char	*path;

	path = NULL;
	if (!(path = (char*)malloc(sizeof(char) * PATH_MAX)))
		return (2);
	if (getcwd(path, PATH_MAX) == NULL)
	{
		write(2, "pwd: error retrieving current directory: getcwd: cannot ", 56);
		write(2, "access parent directories: No such file or directory\n", 53);
		return (1);
	}
	ft_putstr(path);
	write(1, "\n", 1);
	free(path);
	return (0);
}
