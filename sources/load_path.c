/*
** load_path.c for function which will load the path in /home/gaspar_q/rendu/semestre_2/Systeme_Unix/PSU_2014_minishell2
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Tue Feb 17 10:57:31 2015 quentin gasparotto
** Last update Tue Feb 17 11:46:52 2015 quentin gasparotto
*/

#include "../include/minishell.h"

int	load_path(char **env, char ***pathes)
{
  int	var_path;

  if (*pathes != NULL)
    {
      free_wordtab(*pathes);
      *pathes = NULL;
    }
  var_path = find_env_var("PATH", env);
  if (env[var_path] != NULL)
    {
      if ((*pathes = get_args(&env[var_path][my_strlen("PATH=")], ":")) == NULL)
	return (PATH_ERR);
    }
  return (CLEAN);
}
