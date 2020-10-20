/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:09:43 by grigo             #+#    #+#             */
/*   Updated: 2020/10/20 16:27:07 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_access(char *bin)
{
	int		fd;

	if ((fd = open(bin, O_RDONLY)) > 0)
		return (0);
	else
		return (-1);
}

char	*creatbin(char **split_path, char **cmd)
{
	char	*bin;
	int		i;

	i = 0;
	while (split_path[i])
	{
		if (!(bin = (char *)ft_calloc(sizeof(char),
			(ft_strlen(split_path[i]) + 1 + ft_strlen(cmd[0])) + 1)))
			return (NULL);
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
	return (bin);
}

bool	get_path(char **cmd, char **env)
{
	char	*path;
	char	*bin;
	char	**split_path;
	int		i;

	path = NULL;
	split_path = NULL;
	if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) != 0)
	{
		i = 0;
		while (env[i])
		{
			if (!ft_strncmp(env[i], "PATH=", 5))
			{
				path = ft_strdup(&env[i][5]);
				break ;
			}
			i++;
		}
		if (path == NULL)
			return (false);
		split_path = ft_split(path, ':');
		free(path);
		path = NULL;
		bin = creatbin(split_path, cmd);
	}
	else
	{
		free(path);
		path = NULL;
		return (true);
	}
	return (bin == NULL ? false : true);
}
