/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:23:14 by grigo             #+#    #+#             */
/*   Updated: 2020/11/10 11:45:58 by grigo            ###   ########.fr       */
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
		g_pid[0] = 0;
	}
	if (g_fd[1] != 0 && g_cvr[1])
	{
		close(0);
		if (dup2(g_fd[1], 0) == -1)
			write(2, "error: dup2 failed\n", 19);
		close(g_file[1]);
		close(g_fd[1]);
		g_fd[1] = 0;
		g_pid[0] = 0;
	}
}

void	exect_command(char **commande, char ***env)
{
	char	**tenv;

	tenv = ft_getenv(*env);
	if (get_path(commande, tenv) == true)
		cmd_execution(commande, *env);
	else
		ft_puterror("bash: ", commande[0], ": command not found\n", 127);
	ft_splitdel(&tenv);
	tenv = NULL;
}

char	*ft_command(char *line, char ***env)
{
	char	**command;

	command = NULL;
	if (ft_strchr(line, '$'))
	{
		if ((line = variables1(line, *env)) == NULL)
			return (line);
		if (!ft_strcmp(line, "\0"))
			return (line);
	}
	if ((command = creat_list_arg(line)) == NULL)
		return (line);
	if ((command = detectcmd(command)) == NULL)
		return (line);
	command = ft_backslash(command, 0);
	if (command == NULL)
		write(1, "", 0);
	else if (ft_strcmp(command[0], "exit") == 0)
		errno = ft_exit(command);
	else if (built_command(command[0]))
		exect_built_commande(command, env);
	else
		exect_command(command, env);
	if (command)
		ft_splitdel(&command);
	ft_closefile();
	return (line);
}

int		ft_precommande(char *line, char ***env)
{
	char	**command;
	int		i;
	int		nbpipe;

	command = NULL;
	if (ft_checkerror(line))
		return (0);
	while (line[0] == ' ' || line[0] == ';')
		line += 1;
	if ((command = ft_splitcmd(line)) == NULL)
		return (0);
	i = 0;
	while (command[i])
	{
		command[i] = my_redirection(command[i]);
		if ((nbpipe = ft_nbpipe2(command[i])) != 0)
			ft_pipe(command[i], env, nbpipe);
		else
			command[i] = ft_command(command[i], env);
		i++;
	}
	ft_splitdel(&command);
	return (1);
}
