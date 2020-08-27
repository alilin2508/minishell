/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:52:31 by grigo             #+#    #+#             */
/*   Updated: 2019/11/15 14:47:47 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_put_padding_p(t_opt *f, int len)
{
	int		preci;
	int		width;

	width = f->width;
	preci = f->precision;
	write(1, "0x", 2);
	if (f->zero == 1)
		while (width-- > len)
			write(1, "0", 1);
	else
		while (preci-- > len)
			write(1, "0", 1);
}

void	ft_putstr(char *str, t_opt *f, int len)
{
	int	i;

	i = 0;
	if (f->neg == 1 && f->precision <= len && f->zero != 1)
		write(1, "-", 1);
	if (f->conv == 'p')
		ft_put_padding_p(f, len);
	if (f->conv == 'c' && str[0] == '\0')
		write(1, "\0", 1);
	else
	{
		while (str[i])
		{
			ft_putchar(str[i]);
			i++;
		}
	}
}
