/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:09:55 by grigo             #+#    #+#             */
/*   Updated: 2019/11/15 14:56:51 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"

int		g_result;
int		g_lentoto;

typedef struct	s_opt
{
	int		left;
	int		zero;
	int		width;
	int		precision;
	int		neg;
	char	conv;
	char	*fmrt;
}				t_opt;

int				ft_printf(const char *format, ...);
int				ft_check(t_opt *f, va_list ap);
void			ft_print(t_opt *f, va_list ap);
void			ft_put(t_opt *f, int len, char *str);
void			ft_putint(t_opt *f, int len, char *str);
void			ft_result(t_opt *f);
char			*ft_itoa_base(long value, char *base);
void			ft_putstr(char *str, t_opt *f, int len);
void			ft_return(t_opt *f, int len);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
void			ft_putnbr(int nb);
char			*ft_strdup(const char *s1);
int				ft_isdigit(int c);
size_t			ft_strlen(const char *s);
int				ft_islowalpha(int c);
char			*ft_substr(char const *s, unsigned int start,
		size_t len);
void			ft_putchar(char c);
void			ft_putc(t_opt *f, va_list ap);
char			*ft_strnull(t_opt *f);
int				ft_stars(t_opt *f, va_list ap);
void			ft_putu(t_opt *f, va_list ap);
void			ft_putspe(char c);
void			ft_putleft(int tmp, t_opt *f, char *str, int len);

#endif
