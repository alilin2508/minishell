/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 18:57:34 by alilin            #+#    #+#             */
/*   Updated: 2020/11/12 14:29:57 by gabrielri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(char **tmp)
{
	int i;
	int j;

	i = 0;
	while (tmp[i])
	{
		write(1, "export ", 7);
		j = 0;
		while (tmp[i][j] != '=' && tmp[i][j])
		{
			write(1, &tmp[i][j], 1);
			j++;
		}
		if (tmp[i][j] != '\0')
		{
			write(1, &tmp[i][j], 1);
			j++;
			write(1, "\"", 1);
			write(1, &tmp[i][j], ft_strlen(&tmp[i][j]));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}

void	alph_sort(char **tmp, int i, int j, int k)
{
	int		flag;
	char	*comp;
	char	*temp;

	flag = 0;
	while (tmp[i])
	{
		comp = NULL;
		comp = ft_strdup(tmp[i]);
		k = i + 1;
		while (tmp[k])
		{
			j = 0;
			if (comp[j] > tmp[k][j])
			{
				free(comp);
				comp = ft_strdup(tmp[k]);
				flag = k;
			}
			else if (comp[j] == tmp[k][j])
			{
				while ((comp[j] != '=' && tmp[k][j] != '=') && (comp[j] == tmp[k][j]))
					j++;
				if (comp[j] > tmp[k][j])
				{
					free(comp);
					comp = ft_strdup(tmp[k]);
					flag = k;
				}
			}
			k++;
		}
		if (ft_strcmp(tmp[i], comp) != 0)
		{
			temp = NULL;
			temp = ft_strdup(tmp[i]);
			free(tmp[i]);
			tmp[i] = ft_strdup(comp);
			free(tmp[flag]);
			tmp[flag] = ft_strdup(temp);
			free(temp);
		}
		free(comp);
		i++;
	}
	print_export(tmp);
}

char	**sort_export(char **env)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	if (!(tmp = (char **)malloc(sizeof(char *) * tab_len(env))))
		return (env);
	while (env[i])
	{
		if (ft_strncmp(env[i], "_=", 2) != 0)
		{
			if (!(tmp[j] = (char *)malloc(sizeof(char) *
					ft_strlen(env[i]) + 1)))
				return (env);
			ft_strcpy(tmp[j], env[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	alph_sort(tmp, 0, 0, 0);
	ft_splitdel(&tmp);
	return (env);
}
