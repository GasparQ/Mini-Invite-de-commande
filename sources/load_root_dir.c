/*
** load_root_dir.c for load root directory of user in /home/gaspar_q/rendu/Systeme_Unix/PSU_2014_minishell1
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Tue Jan 13 13:07:41 2015 quentin gasparotto
** Last update Tue Jan 13 16:45:40 2015 quentin gasparotto
*/

#include "../include/minishell.h"

int	load_root(char ***env)
{
  int	var;
  char	*root;

  var = find_env_var("USER", *env);
  if ((*env)[var] != NULL)
    {
      if ((root = str_fusion("/home", &(*env)[var][5], '/')) == NULL)
	return (my_strerror(MALLOC_ERR));
      if (chdir(root) == ERROR)
	my_strerror(CD_ERR);
      else
	{
	  var = find_env_var("PWD", *env);
	  if ((*env)[var] != NULL)
	    {
	      free((*env)[var]);
	      if (((*env)[var] = str_fusion("PWD", root, '=')) == NULL)
		return (my_strerror(MALLOC_ERR));
	    }
	}
      free(root);
    }
  return (CLEAN);
}
