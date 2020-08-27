/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 10:00:51 by grigo             #+#    #+#             */
/*   Updated: 2019/11/15 14:45:24 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	t_opt		f;

	g_lentoto = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			g_result = 0;
			f.fmrt = (char *)&*format;
			ft_check(&f, ap);
			ft_print(&f, ap);
			format += g_result;
		}
		else
		{
			ft_putchar(*format);
			format++;
			g_lentoto++;
		}
	}
	va_end(ap);
	return (g_lentoto);
}
