/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:23:14 by grigo             #+#    #+#             */
/*   Updated: 2020/10/20 14:45:29 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_closefile(void)
{
	if (g_fd[0] != 0 && g_cvr[0])
	{
		close(STDOUT_FILENO);
		if (dup2(g_fd[0], STDOUT_FILENO) == -1)
			write(2, "error: dup2 failed\n", 19);
		close(g_file[0]);
		close(g_fd[0]);
		g_fd[0] = 0;
	}
	if (g_fd[1] != 0 && g_cvr[1])
	{
		close(0);
		if (dup2(g_fd[1], 0) == -1)
			write(2, "error: dup2 failed\n", 19);
		close(g_file[1]);
		close(g_fd[1]);
		g_fd[1] = 0;
	}
}

void	exect_command(char **commande, char ***env)
{
	char	**tenv;

	tenv = ft_getenv(*env);
	if (get_path(commande, tenv) == true)
		cmd_execution(commande);
	else
	{
		ft_puterror("bash: ", commande[0], ": command not found\n");
		errno = 127;
	}
	ft_splitdel(&tenv);
	tenv = NULL;
}

int		ft_commande(char *line, char ***env)
{
	char	**commande;
	char	**tenv;

	commande = NULL;
	tenv = NULL;
	if ((variables1(line, *env)) == NULL)
		return (0);
	if ((commande = creat_list_arg(line)) == NULL)
		return (0);
	commande = detectcmd(commande);
	if (commande == NULL)
		write(1, "", 0);
	else if (ft_strcmp(commande[0], "exit") == 0)
		ft_exit(commande);
	else if (built_command(commande[0]))
		exect_built_commande(commande, env);
	else
		exect_command(commande, env);
	if (commande)
		ft_splitdel(&commande);
	ft_closefile();
	return (1);
}

int		ft_precommande(char *line, char ***env)
{
	char	**commande;
	int		i;
	int		nbpipe;

	commande = NULL;
	if (ft_checkerror(line))
		return (0);
	while (line[0] == ' ' || line[0] == ';')
		line += 1;
	if ((commande = ft_splitcmd(line)) == NULL)
		return (0);
	i = 0;
	while (commande[i])
	{
		my_redirection(commande[i]);
		if ((nbpipe = ft_nbpipe2(commande[i])) != 0)
			ft_pipe(commande[i], env, nbpipe);
		else
			ft_commande(commande[i], env);
		i++;
	}
	ft_splitdel(&commande);
	return (1);
}
