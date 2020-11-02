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

char  **ft_free(char **freed)
{
  ft_splitdel(&freed);
  return (NULL);
}
