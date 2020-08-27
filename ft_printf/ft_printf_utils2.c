/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 11:54:11 by grigo             #+#    #+#             */
/*   Updated: 2019/11/15 14:47:22 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				ft_stars(t_opt *f, va_list ap)
{
	int		nb;

	nb = va_arg(ap, int);
	if (nb < 0)
	{
		nb *= -1;
		f->left = 1;
		f->zero = 0;
	}
	return (nb);
}

void			ft_putu(t_opt *f, va_list ap)
{
	char			*str;
	int				len;
	unsigned int	varg;

	varg = va_arg(ap, unsigned int);
	if (varg == 0 && f->precision == 0)
		str = "\0";
	else
		str = ft_itoa(varg);
	len = ft_strlen(str);
	ft_return(f, len);
	ft_putint(f, len, str);
	if (varg != 0 && f->precision != 0)
		free(str);
}

void			ft_putspe(char c)
{
	ft_putchar(c);
	g_lentoto += 1;
}

void			ft_putleft(int tmp, t_opt *f, char *str, int len)
{
	if (f->left > 0)
		ft_putstr(str, f, len);
	if (len < f->width)
		while (f->width - tmp++ != 0)
			write(1, " ", 1);
	if (f->left < 1)
		ft_putstr(str, f, len);
}
