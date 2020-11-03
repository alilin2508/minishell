#include "minishell.h"

int   ft_strcmparg(char *str)
{
  int   i;

  i = 1;
  if (str[0] != '-')
    return (0);
  while (str[i] && str[i] == 'n')
    i++;
  if (str[i] != '\0')
    return (0);
  return (1);
}

char    **ft_strerror(char *str, char **cmd)
{
  ft_puterror("bash: ", str, ": ", errno);
  write(2, strerror(errno), ft_strlen(strerror(errno)));
  write(2, "\n", 1);
  ft_splitdel(&cmd);
  return (NULL);
}
