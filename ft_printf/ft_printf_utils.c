/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:31:59 by grigo             #+#    #+#             */
/*   Updated: 2019/11/15 14:30:08 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_putint(t_opt *f, int len, char *str)
{
	int		preci;
	int		width;

	preci = f->precision;
	width = f->width;
	if (preci > -1)
		f->zero = 0;
	if (preci > len)
	{
		if (f->width > preci && f->left == 0)
		{
			while (f->width-- > preci)
				write(1, " ", 1);
		}
		if (f->neg == 1)
			write(1, "-", 1);
		if (f->conv != 'p')
			while (preci-- - len > 0)
				write(1, "0", 1);
		f->width -= (f->precision - len);
		ft_put(f, len, str);
	}
	else
		ft_put(f, len, str);
}

void	ft_put(t_opt *f, int len, char *str)
{
	int		tmp;

	tmp = len;
	if (f->left > 0 || (f->zero < 1 && f->width > 0))
		ft_putleft(tmp, f, str, len);
	else if (f->zero > 0 && f->conv != 'p')
	{
		if (f->neg == 1)
			write(1, "-", 1);
		if (len < f->width)
			while (f->width - tmp++ != 0)
				write(1, "0", 1);
		ft_putstr(str, f, len);
	}
	else
		ft_putstr(str, f, len);
}

void	ft_return(t_opt *f, int len)
{
	if (f->conv == 'd' || f->conv == 'i' || f->conv == 'u'
			|| f->conv == 'x' || f->conv == 'X' || f->conv == 'p')
	{
		if (f->precision >= len && f->precision >= f->width)
			g_lentoto += f->precision;
		else if (f->width >= len && f->precision <= f->width)
			g_lentoto += f->width;
		else if (f->precision <= len && len >= f->width)
			g_lentoto += len;
	}
	else
	{
		if (len > f->width)
			g_lentoto += len;
		if (len <= f->width)
			g_lentoto += f->width;
	}
}

void	ft_putc(t_opt *f, va_list ap)
{
	char	c;
	char	*str;

	c = va_arg(ap, int);
	if (!(str = (char *)malloc(sizeof(char) * 1 + 1)))
		return ;
	str[0] = c;
	str[1] = '\0';
	ft_return(f, 1);
	ft_put(f, 1, str);
	free(str);
}

char	*ft_strnull(t_opt *f)
{
	char	*str;

	str = "(null)";
	if (f->precision > -1)
		str = ft_substr(str, 0, f->precision);
	else
		str = ft_strdup(str);
	return (str);
}
