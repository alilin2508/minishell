/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:15:26 by grigo             #+#    #+#             */
/*   Updated: 2019/10/08 19:26:50 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dupdst;
	unsigned char	*dupsrc;
	int				i;

	i = 0;
	dupdst = (unsigned char *)dst;
	dupsrc = (unsigned char *)src;
	while (n-- > 0)
	{
		dupdst[i] = dupsrc[i];
		if (dupsrc[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (0);
}
