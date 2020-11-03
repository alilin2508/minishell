/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:13:00 by grigo             #+#    #+#             */
/*   Updated: 2020/10/29 10:57:13 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <math.h>
# include <errno.h>
# include <memory.h>
# include <signal.h>
# include <dirent.h>
# include <stdbool.h>
# include <sys/wait.h>
# include "../libft/includes/libft.h"

int			g_file[3];
int			g_fd[2];
int			g_cvr[2];
pid_t		g_pid[2];
# define PATH_MAX 4096

char	*ft_checkredir(char *str);
int		ft_checkerror(const char *str);
int		ft_exit(char **commande);
char	**my_redir_right(char **cmd, int idx, int f_open[2]);
int		ft_precommande(char *line, char ***env);
char	*my_redirection(char *str);
char	**detectcmd(char **cmd);
bool	get_path(char **cmd, char **env);
char	**ft_getenv(char **env);
char	*my_getenv(char **env, char *path);
void	cmd_execution(char **cmd, char **env);
int		environment(char **cmd, char **env);
size_t	path_max(char **env);
int		position(void);
int		my_cd(char *path, char ***env);
int		ft_access(char *bin);
void	exect_built_commande(char **cmd, char ***env);
int		built_command(char *cmd);
char	*ft_command(char *line, char ***env);
void	end(int sig);
void	recovery(int sig);
char	*variables1(char *str, char **env);
int		ft_checkerror(const char *str);
char	**creat_list_arg(char *line);
char	**ft_splitcmd(char *str);
void	ft_pipe(char *str, char ***env, int nb);
int		ft_nbpipe2(const char *str);
void	ft_checkpipe(char *str);
int		parse_error(int t_e, char *err);
void	ft_puterror(char *errorstart, char *arg, char *errorend, int err);
int		ft_checkex2(char *cmd, char **env);
int		ft_checkunset(char *cmd, char **env);
int		tab_len(char **env);
int		ft_echo(char **cmd);
int		ft_cword(char *line);
int		ft_sepcount(char *line, char c);
char	**detectcmd(char **cmd);
char	**my_redir_left(char **cmd, int idx, int f_open[2]);
char	**delet_chevron(char **cmd, int idx);
char	**ft_export(char **cmd, char **env);
char	**ft_unset(char **cmd, char **env);
int		passquotes(const char *str, int i, int c);
int		ft_pass_space(char *str, int i);
char  **ft_backslash(char **cmd, int i);
int 	delspace(char *str, int c);
char  *ft_checkbackredir(char *str, int i);
int   ft_strcmparg(char *str);
char  **ft_strerror(char *str, char **cmd);

#endif
