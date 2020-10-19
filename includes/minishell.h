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

extern int  errno ;
int         g_file[3];
int         g_fd[2];
int 				g_cvr[2];
# define    PATH_MAX 4096

char 		      **my_redir_right(char **cmd, int idx, int f_open[2]);
void          my_redirection(char *str);
char 		      **detectcmd(char **cmd);
static bool   get_path(char **cmd, char **env);
char          **ft_getenv(char **env);
char          *my_getenv(char **env, char *path);
static void   cmd_execution(char **cmd);
void          environment(char **env);
size_t        path_max(char **env);
void          position(char **env);
void          my_cd(char *path, char **env);
int           ft_access(char *bin);
static void   exect_built_commande(char **cmd, char ***env);
int 				  built_command(char *cmd);
int           ft_commande(char *line, char ***env);

#endif
