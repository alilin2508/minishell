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
# include "../libft/libft.h"

static void   get_path(char **cmd, char **env);
char          **ft_getenv(char **env);
char          *my_getenv(char **env, char *path);
static void   cmd_execution(char **cmd);

#endif
