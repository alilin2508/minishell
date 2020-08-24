/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:49:09 by grigo             #+#    #+#             */
/*   Updated: 2019/10/08 12:14:49 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dupdst;

	dupdst = (unsigned char *)dst;
	while (n-- > 0)
	{
		*dupdst = *(unsigned char *)src;
		dupdst++;
		src++;
	}
	return (dst);
}
