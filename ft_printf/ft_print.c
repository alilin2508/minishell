/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:09:59 by grigo             #+#    #+#             */
/*   Updated: 2019/11/18 15:14:54 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_putd(t_opt *f, va_list ap)
{
	char			*str;
	int				len;
	long			va_arg;

	va_arg = va_arg(ap, int);
	if (va_arg < 0)
	{
		va_arg *= -1;
		f->neg = 1;
		f->width--;
		g_lentoto++;
	}
	if (va_arg == 0 && f->precision == 0)
		str = "\0";
	else
		str = ft_itoa(va_arg);
	len = ft_strlen(str);
	ft_return(f, len);
	ft_putint(f, len, str);
	if (va_arg != 0 && f->precision != 0)
		free(str);
}

void	ft_putx(t_opt *f, va_list ap)
{
	char			*str;
	int				len;
	int				i;
	unsigned int	varg;

	i = 0;
	varg = va_arg(ap, unsigned int);
	if (varg == 0 && f->precision == 0)
		str = "\0";
	else
		str = ft_itoa_base(varg, "0123456789abcdef");
	len = ft_strlen(str);
	ft_return(f, len);
	if (f->conv == 'X')
		while (i < len)
		{
			if (ft_islowalpha(str[i]))
				str[i] -= 32;
			i++;
		}
	ft_putint(f, len, str);
	if (varg != 0 && f->precision != 0)
		free(str);
}

void	ft_putp(t_opt *f, va_list ap)
{
	char			*str;
	int				len;
	long			varg;

	varg = va_arg(ap, long);
	if (varg == 0 && f->precision == 0)
		str = "\0";
	else
		str = ft_itoa_base(varg, "0123456789abcdef");
	len = ft_strlen(str) + 2;
	if (f->precision > -1)
	{
		f->precision += 2;
		f->zero = 0;
	}
	ft_return(f, len);
	if (f->zero != 1)
		ft_putint(f, len, str);
	else
		ft_putstr(str, f, len);
	if (varg != 0 && f->precision != 0)
		free(str);
}

void	ft_puts(t_opt *f, va_list ap)
{
	char	*str;
	int		len;
	char	*varg;

	varg = va_arg(ap, char *);
	if (varg == NULL)
		str = ft_strnull(f);
	else if (f->precision > -1)
		str = ft_substr(varg, 0, f->precision);
	else
		str = ft_strdup(varg);
	len = ft_strlen(str);
	ft_return(f, len);
	ft_put(f, len, str);
	free(str);
}

void	ft_print(t_opt *f, va_list ap)
{
	if (f->left == 1)
		f->zero = 0;
	if (f->conv == 'd' || f->conv == 'i')
		ft_putd(f, ap);
	else if (f->conv == 's')
		ft_puts(f, ap);
	else if (f->conv == 'c')
		ft_putc(f, ap);
	else if (f->conv == 'x' || f->conv == 'X')
		ft_putx(f, ap);
	else if (f->conv == 'p')
		ft_putp(f, ap);
	else if (f->conv == 'u')
		ft_putu(f, ap);
}
