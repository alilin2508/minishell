/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_env_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 18:58:01 by grigo             #+#    #+#             */
/*   Updated: 2020/11/07 17:41:18 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_checkex2_1(char **env, char *cmd, int len, int i)
{
  while (env[i])
  {
    if (ft_strncmp(cmd, env[i], len) == 0)
      return (1);
    i++;
  }
  return (0);
}

int		ft_checkex2_2(char **env, char *cmd, int len, int i)
{
  int   j;

  while (env[i])
  {
    if (ft_strncmp(cmd, env[i], len) == 0)
    {
      j = 0;
      while (env[i][j] == cmd[j] && cmd[j] && env[i][j])
        j++;
      if (env[i][j] == '=' || env[i][j] == '\0')
        return (1);
    }
    i++;
  }
  return (0);
}

int   ft_strlenidx(char *cmd, int i)
{
  while (cmd[i] != '=')
    i++;
  if (cmd[i - 1] != '+')
    return (-1);
  return (i + 1);
}

char  *take_tenv(char *cmd, int i)
{
  char  *t_env;

  if (!(t_env = (char *)malloc(sizeof(char) * i)))
    return (NULL);
  while (cmd[i] != '+')
  {
    t_env[i] = cmd[i];
    i++;
  }
  t_env[i] = '=';
  t_env[i + 1] = '\0';
  return (t_env);
}

char  **ft_add_env_export(char *cmd, char **env, char **tmp, int i)
{
  char  *t_env;
  int   len;

  t_env = NULL;
  if ((len = ft_strlenidx(cmd, 0)) == -1)
    return (env);
  if ((t_env = take_tenv(cmd, 0)) == NULL)
    return (env);
  while (env[i])
  {
    if (!ft_strncmp(env[i], t_env, ft_strlen(t_env)))
    {
      ft_strcat(env[i], &cmd[len]);
      free(t_env);
      return (env);
    }
    i++;
  }
  ft_strcat(t_env, &cmd[len]);
  tmp = ft_get_ex_tmp(t_env, env, 0);
  env = ft_get_ex_env(env, tmp, 0);
  free(t_env);
  return (env);
}
