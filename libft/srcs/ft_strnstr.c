/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:36:12 by grigo             #+#    #+#             */
/*   Updated: 2019/10/07 18:57:05 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	posi;
	size_t	j;

	if (!*needle)
		return ((char *)haystack);
	posi = 0;
	while (haystack[posi] && posi < len)
	{
		j = 0;
		while (haystack[posi + j] == needle[j] && posi + j < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[posi]);
			j++;
		}
		posi++;
	}
	return (0);
}
