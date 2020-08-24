/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:03:51 by grigo             #+#    #+#             */
/*   Updated: 2019/10/16 14:17:36 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		ft_strncat(char *dst, char *src, size_t nb)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (src[j] && j < nb)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (*dst);
}

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen((char *)src);
	if (len_dst >= dstsize)
		return (dstsize + len_src);
	if (len_src < dstsize - len_dst)
		ft_strncat(dst, (char *)src, len_src + 1);
	else
	{
		ft_strncat(dst, (char *)src, dstsize - len_dst - 1);
		dst[dstsize - 1] = '\0';
	}
	return (len_dst + len_src);
}
