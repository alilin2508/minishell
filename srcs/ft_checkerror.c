/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkerror.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 14:26:27 by grigo             #+#    #+#             */
/*   Updated: 2020/10/22 14:51:15 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_redir_right_error(const char *str, int i)
{
	int		err;

	if (str[i + 1] == '>' && str[i + 2] == '>')
		return (parse_error(1, ">"));
	if (str[i + 1] == ' ' || str[i + 1] == '\0' || (str[i + 1] == '>' &&
		(str[i + 2] == ' ' || str[i + 2] == '\0')) || str[i + 1] == '<')
	{
		if (str[i + 1] == '>')
			err = i + 2;
		else
			err = i + 1;
		while (str[err] && str[err] == ' ')
			err++;
		if (str[err] == '\0')
			return (parse_error(1, "newline"));
		if (str[err] == '>')
			return (parse_error(1, ">"));
		if (str[err] == '<')
			return (parse_error(1, "<"));
		if (str[err] == '|')
			return (parse_error(1, "|"));
	}
	return (0);
}

int			ft_redir_left_error(const char *str, int i)
{
	int err;

	if (str[i + 1] == '<' || str[i + 1] == '>' || str[i + 1] == '\0')
		return (parse_error(1, "newline"));
	if (str[i + 1] == ' ' || str[i + 1] == '\0')
	{
		err = i + 1;
		while (str[err] && str[err] == ' ')
			err++;
		if (str[err] == '\0')
			return (parse_error(1, "newline"));
		if (str[err] == '<')
			return (parse_error(1, "<"));
		if (str[err] == '>')
			return (parse_error(1, ">"));
		if (str[err] == '|')
			return (parse_error(1, "|"));
	}
	return (0);
}

int			ft_pipe_error(const char *str, int i)
{
	int		err;

	if (str[i + 1] == '|' || i == 0)
		return (parse_error(1, "|"));
	if (str[i + 1] == ' ' || str[i + 1] == '\0')
	{
		err = i + 1;
		while (str[err] && str[err] == ' ')
			err++;
		if (str[err] == '\0')
			return (parse_error(1, "newline"));
		if (str[err] == '|')
			return (parse_error(1, "|"));
	}
	return (0);
}

int			ft_parse_error(const char *str, int i)
{
	int		err;
	int		c;

	if (str[i] == '\'' || str[i] == '"')
	{
		c = str[i];
		i++;
		while (str[i] && str[i] != c)
			i++;
		if (str[i] == '\0')
			return(parse_error(2, NULL));
	}
	else if (str[i] == ';')
	{
		if (i == 0)
			return (parse_error(1, ";"));
		err = i + 1;
		while (str[err] == ' ')
			err++;
		if (str[err] == ';')
			return (parse_error(1, ";"));
	}
	return (i);
}

int			ft_checkerror(const char *str)
{
	int		i;
	int		err;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"' || str[i] == ';')
			if ((i = ft_parse_error(str, i)) == -1)
				return (1);
		if (str[i] == '>')
			if ((err = ft_redir_right_error(str, i)) != 0)
				return (err);
		if (str[i] == '<')
			if ((err = ft_redir_left_error(str, i)) != 0)
				return (err);
		if (str[i] == '|')
			if ((err = ft_pipe_error(str, i)) != 0)
				return (err);
		i++;
	}
	return (0);
}
