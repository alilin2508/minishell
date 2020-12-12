/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkerror.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 14:26:27 by grigo             #+#    #+#             */
/*   Updated: 2020/12/08 14:44:59 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_redir_right_error(const char *str, int i)
{
	int		err;

	if (str[i + 1] == '>' && str[i + 2] == '>' && str[i + 3] == '>')
		return (parse_error(1, ">>"));
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

int		ft_redir_left_error(const char *str, int i)
{
	int		err;

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

int		ft_pipe_error(const char *str, int i)
{
	int		err;

	if (str[i + 1] == '|' && str[i + 2] == '|')
		return (parse_error(1, "||"));
	if (i == 0)
		return (parse_error(1, "|"));
	err = i - 1;
	while (str[err] == ' ' && err > 0)
		err--;
	if (err == 0 && str[err] == ' ')
		return (parse_error(1, "|"));
	err = i + 1;
	while (str[err] && str[err] == ' ')
		err++;
	if (str[err] == '\0')
		return (parse_error(1, "newline"));
	if (str[err] == '|')
		return (parse_error(1, "|"));
	if (str[err] == ';')
		return (parse_error(1, ";"));
	return (0);
}

int		ft_semicolon_error(const char *str, int i)
{
	int		err;

	if (str[i + 1] == ';')
		return (parse_error(1, ";;"));
	if (i == 0)
		return (parse_error(1, ";"));
	err = i - 1;
	while (str[err] == ' ' && err > 0)
		err--;
	if (err == 0)
		return (parse_error(1, ";"));
	err = i + 1;
	while (str[err] == ' ')
		err++;
	if (str[err] == ';')
		return (parse_error(1, ";"));
	else if (str[err] == '|')
		return (parse_error(1, "|"));
	return (0);
}

int		ft_checkerror(const char *str, int i)
{
	int		err;

	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			if ((i = passquotes(str, i + 1, str[i])) == -1)
				return (parse_error(2, NULL));
		if (str[i] == ';')
			if ((err = ft_semicolon_error(str, i)) != 0)
				return (err);
		if (str[i] == '>')
			if ((err = ft_redir_right_error(str, i)) != 0)
				return (err);
		if (str[i] == '<')
			if ((err = ft_redir_left_error(str, i)) != 0)
				return (err);
		if (str[i] == '|')
			if ((err = ft_pipe_error(str, i)) != 0)
				return (err);
		if (str[i] == '\\')
			i++;
		i++;
	}
	return (0);
}
