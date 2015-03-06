/*
** change_previous.c for change to the previous directory in /home/gaspar_q/rendu/semestre_2/Systeme_Unix/PSU_2014_minishell2/sources
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Fri Feb 27 16:22:10 2015 quentin gasparotto
** Last update Wed Mar  4 20:48:44 2015 quentin gasparotto
*/

#include "../include/minishell.h"

int	change_previous(char ***env)
{
  char	**new_args;
  char	*new_cmd;
  int	var;

  var = find_env_var("OLDPWD", *env);
  if ((*env)[var] == NULL)
    return (CLEAN);
  if ((new_cmd =
       str_fusion("cd", &((*env)[var][my_strlen("OLDPWD=")]), ' ')) == NULL)
    return (my_strerror(MALLOC_ERR));
  if ((new_args = get_args(new_cmd, " \t")) == NULL)
    return (CLEAN);
  free(new_cmd);
  change_directory(new_args, env);
  free_wordtab(new_args);
  return (CLEAN);
}
