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

int         g_file[3];
int         g_fd[2];
int 				g_cvr[2];
pid_t 	    g_pid[2];
# define    PATH_MAX 4096

char          *ft_checkredir(char *str);
int 		      ft_checkerror(const char *str);
int 					ft_exit(char **commande);
char 		      **my_redir_right(char **cmd, int idx, int f_open[2]);
int 				  ft_precommande(char *line, char ***env);
char          *my_redirection(char *str);
char 		      **detectcmd(char **cmd);
bool          get_path(char **cmd, char **env);
char          **ft_getenv(char **env);
char          *my_getenv(char **env, char *path);
void          cmd_execution(char **cmd);
int           environment(char **cmd, char **env);
size_t        path_max(char **env);
int           position(void);
int           my_cd(char *path, char **env);
int           ft_access(char *bin);
void          exect_built_commande(char **cmd, char ***env);
int 				  built_command(char *cmd);
char          *ft_command(char *line, char ***env);
void 				  end(int sig);
void 				  recovery(int sig);
char 					*variables1(char *str, char **env);
int 		      ft_checkerror(const char *str);
char 					**creat_list_arg(char *line);
char 		      **ft_splitcmd(char *str);
void 				  ft_pipe(char *str, char ***env, int nb);
int 		      ft_nbpipe2(const char *str);
void          ft_checkpipe(char *str);
int           parse_error(int t_e, char *err);
void          ft_puterror(char *errorstart, char *arg, char *errorend, int err);
int           ft_checkex2(char *cmd, char **env);
int           ft_checkunset(char *cmd, char **env);
int           tab_len(char **env);

#endif
