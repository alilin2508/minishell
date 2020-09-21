#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <math.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"

extern int errno ;

static bool   get_path(char **cmd, char **env);
char          **ft_getenv(char **env);
char          *my_getenv(char **env, char *path);
static void   cmd_execution(char **cmd);
void          environment(char **env);
size_t        path_max(char **env);
void          position(char **cmd, char **env);
void          my_cd(char *path, char **env, char **cmd);
int           ft_access(char *bin);
static void   exect_built_commande(char **cmd, char ***env);
int 				  built_command(char *cmd);
int           ft_commande(char *line, char ***env);

#endif
