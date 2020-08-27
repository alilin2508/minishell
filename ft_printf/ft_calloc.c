/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:38:40 by grigo             #+#    #+#             */
/*   Updated: 2019/11/08 18:39:48 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*al;
	size_t	i;

	i = 0;
	if (!(al = malloc(size * count)))
		return (0);
	while (count > i)
	{
		al[i] = 0;
		i++;
	}
	return (al);
}
