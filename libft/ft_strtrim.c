/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:48:20 by grigo             #+#    #+#             */
/*   Updated: 2019/10/16 14:24:13 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_start_nbset(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		nbset;

	nbset = 0;
	i = 0;
	while (s1[i] && set[j] != '\0')
	{
		j = 0;
		while (s1[i] != set[j] && set[j])
			j++;
		if (s1[i] == set[j])
			nbset++;
		i++;
	}
	return (nbset);
}

static int			ft_end_nbset(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		nbset;

	i = ft_strlen(s1) - 1;
	j = 0;
	nbset = 0;
	while (i > 0 && set[j])
	{
		j = 0;
		while (s1[i] != set[j] && set[j])
			j++;
		if (s1[i] == set[j])
			nbset++;
		i--;
	}
	return (nbset);
}

char				*ft_strtrim(char const *s1, char const *set)
{
	int		size;
	int		start;
	int		end;
	char	*str;
	int		i;

	start = ft_start_nbset(s1, set);
	if (ft_strlen(s1) == (size_t)start)
		return (str = (char *)ft_calloc(1, sizeof(char)));
	end = ft_end_nbset(s1, set);
	size = ft_strlen(s1) - (start + end);
	if (!(str = (char *)malloc((sizeof(char) * (size + 1)))))
		return (0);
	i = 0;
	while ((unsigned long)start < (ft_strlen(s1) - end))
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
