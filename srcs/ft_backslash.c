#include "minishell.h"

char    *ft_deletbackslash(char *cmd, char *tmp, int i, int j)
{
  while (cmd[i])
  {
    if (cmd[i] == '\\')
      i++;
    if (cmd[i] == 3 && cmd[i + 1] == 3)
    {
      i++;
      cmd[i] = '\\';
    }
    else if (cmd[i] == 3)
      cmd[i] = '\\';
    if (cmd[i] != '\0')
      tmp[j] = cmd[i];
    j++;
    i++;
  }
  free(cmd);
  if (!(cmd = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 1))))
    return (NULL);
  ft_strcpy(cmd, tmp);
  free(tmp);
  tmp = NULL;
  return (cmd);
}

char    **ft_backslash(char **cmd, int i)
{
  char  *tmp;

  tmp = NULL;
  while (cmd[i])
  {
    if(ft_strchr(cmd[i], '\\') || ft_strchr(cmd[i], 3))
    {
      if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(cmd[i]) + 1))))
        return (NULL);
      cmd[i] = ft_deletbackslash(cmd[i], tmp, 0, 0);
    }
    i++;
  }
  return (cmd);
}
