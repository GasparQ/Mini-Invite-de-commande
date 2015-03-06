/*
** change_old_pwd.c for change old pwd in /home/gaspar_q/rendu/semestre_2/Systeme_Unix/PSU_2014_minishell2/sources
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Fri Feb 27 16:04:57 2015 quentin gasparotto
** Last update Fri Feb 27 16:42:11 2015 quentin gasparotto
*/

#include "../include/minishell.h"

int	change_old_pwd(char **env, char *pwd)
{
  int	var;
  char	*new_var;

  var = find_env_var("OLDPWD", env);
  if (env[var] == NULL)
    return (ERROR);
  if ((new_var = str_fusion("OLDPWD", &pwd[my_strlen("PWD=")], '=')) == NULL)
    {
      return (my_strerror(MALLOC_ERR));
    }
  free(env[var]);
  env[var] = new_var;
  return (CLEAN);
}
