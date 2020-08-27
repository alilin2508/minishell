/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:51:49 by grigo             #+#    #+#             */
/*   Updated: 2019/11/15 13:45:23 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_initialize(t_opt *f)
{
	f->left = 0;
	f->zero = 0;
	f->width = 0;
	f->neg = 0;
	f->precision = -1;
	f->conv = '\0';
}

int		ft_precision(t_opt *f, int i, va_list ap)
{
	int		j;
	char	*str;

	g_result++;
	j = 0;
	if (f->fmrt[i] == '*')
	{
		f->precision = va_arg(ap, int);
		g_result--;
	}
	else
	{
		while (ft_isdigit(f->fmrt[j + i]))
		{
			j++;
			g_result++;
		}
		g_result -= 1;
		str = ft_substr(f->fmrt, i, j);
		f->precision = ft_atoi((const char *)str);
		free(str);
	}
	return (i + j);
}

int		ft_width(t_opt *f, int i, va_list ap)
{
	int		j;
	char	*str;

	j = 0;
	if (f->fmrt[i] == '*')
	{
		f->width = ft_stars(f, ap);
		j += 1;
	}
	else
	{
		while (ft_isdigit(f->fmrt[j + i]))
		{
			j++;
			g_result++;
		}
		g_result -= 1;
		if (j > 0)
		{
			str = ft_substr(f->fmrt, i, j);
			f->width = ft_atoi((const char *)str);
			free(str);
		}
	}
	return (i + j);
}

void	ft_conv(t_opt *f, int i)
{
	if (f->fmrt[i] == 'c')
		f->conv = 'c';
	else if (f->fmrt[i] == 's')
		f->conv = 's';
	else if (f->fmrt[i] == 'p')
		f->conv = 'p';
	else if (f->fmrt[i] == 'd')
		f->conv = 'd';
	else if (f->fmrt[i] == 'i')
		f->conv = 'i';
	else if (f->fmrt[i] == 'u')
		f->conv = 'u';
	else if (f->fmrt[i] == 'x')
		f->conv = 'x';
	else if (f->fmrt[i] == 'X')
		f->conv = 'X';
	else
		f->conv = '\0';
}

int		ft_check(t_opt *f, va_list ap)
{
	int		i;

	ft_initialize(f);
	i = 1;
	while (f->fmrt[i] == '0' || f->fmrt[i] == '.' || f->fmrt[i] == '-'
			|| ft_isdigit(f->fmrt[i]) || f->fmrt[i] == '*')
	{
		g_result++;
		if (f->fmrt[i] == '0')
			f->zero = 1;
		else if (f->fmrt[i] == '-')
			f->left = 1;
		else if (f->fmrt[i] == '.')
			i = ft_precision(f, i + 1, ap) - 1;
		else if ((ft_isdigit((char)f->fmrt[i]) && f->fmrt[i] != '0'
				&& f->fmrt[i - 1] != '.') || (f->fmrt[i] == '*'
					&& f->fmrt[i - 1] != '.'))
			i = ft_width(f, i, ap) - 1;
		i++;
	}
	if (f->fmrt[1] == '%')
		ft_putspe('%');
	ft_conv(f, i);
	g_result += 2;
	return (0);
}
