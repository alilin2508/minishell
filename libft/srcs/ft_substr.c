/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:49:13 by grigo             #+#    #+#             */
/*   Updated: 2019/10/15 16:00:05 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (start >= ft_strlen(s))
		return (str = (char *)ft_calloc(1, sizeof(char *)));
	if (!(str = (char *)malloc(sizeof(char *) * (len + 1))))
		return (0);
	i = 0;
	while (len-- > 0 && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
