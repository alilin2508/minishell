/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:20:52 by grigo             #+#    #+#             */
/*   Updated: 2020/10/20 17:25:21 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_puterror(char *errorstart, char *arg, char *errorend)
{
	write(2, errorstart, ft_strlen(errorstart));
	write(2, arg, ft_strlen(arg));
	write(2, errorend, ft_strlen(errorend));
}

int		parse_error(int t_e, char *err)
{
	if (t_e == 1)
		ft_puterror("bash: syntax error near unexpected token `", err, "'\n");
	if (t_e == 2)
		write(1, "bash: missing quote\n", 20);
	return (t_e);
}
