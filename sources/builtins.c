/*
** builtins.c for builtins functions in /home/gaspar_q/rendu/Systeme_Unix/PSU_2014_minishell1/sources
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Fri Jan  9 14:05:39 2015 quentin gasparotto
** Last update Wed Mar  4 20:48:16 2015 quentin gasparotto
*/

#include "../include/minishell.h"

int	change_directory(char **args, char ***env)
{
  char	**new_args;

  if (get_nb_of_var(args) == 1)
    {
      if ((new_args = get_args("cd ~", " \t")) == NULL)
	return (CLEAN);
      change_directory(new_args, env);
      free_wordtab(new_args);
    }
  else if (args[1] != NULL)
    {
      if (args[1][0] == '~')
	resolve_home(args, *env, 1);
      else if (args[1][0] == '-')
	return (change_previous(env));
      if (chdir(args[1]) == ERROR)
	return (my_strerror(CD_ERR));
      else
	{
	  resolve_pwd(args, *env);
	}
    }
  return (CLEAN);
}

int	env_builtin(char **args, char ***env)
{
  int	var;

  (void)args;
  var = 0;
  if (*env == NULL || (*env)[0] == NULL)
    my_strerror(NO_ENV);
  else
    {
      while ((*env)[var] != NULL)
	{
	  my_putstr((*env)[var]);
	  my_putchar('\n');
	  var = var + 1;
	}
    }
  return (CLEAN);
}

int	set_environment(char **args, char ***env)
{
  int	arg_var;
  int	nb_of_var;
  char	**new_env;

  if ((nb_of_var = get_nb_of_var(args)) != 4)
    return (my_strerror(SET_ENV_USAGE));
  arg_var = find_env_var(args[1], *env);
  if ((*env)[arg_var] == NULL)
    {
      nb_of_var = get_nb_of_var(*env);
      if ((arg_var = realloc_env(*env, &new_env, nb_of_var + 2)) == MALLOC_ERR)
	return (my_strerror(MALLOC_ERR));
      new_env[arg_var] = str_fusion(args[1], args[2], '=');
      free_wordtab(*env);
      *env = new_env;
    }
  else if (my_getnbr(args[3]) != 0)
    {
      free((*env)[arg_var]);
      (*env)[arg_var] = str_fusion(args[1], args[2], '=');
    }
  if (my_strcmp("PATH", args[1]) != 0)
    return (LOAD_PATH);
  return (CLEAN);
}

int	unset_environment(char **args, char ***env)
{
  int	var;

  if (get_nb_of_var(args) != 2)
    return (my_strerror(UNSETENV_USAGE));
  var = find_env_var(args[1], *env);
  if ((*env)[var] == NULL)
    my_strerror(NO_VAR);
  else
    {
      free((*env)[var]);
      while ((*env)[var] != NULL)
	{
	  (*env)[var] = (*env)[var + 1];
	  var = var + 1;
	}
    }
  if (my_strcmp("PATH", args[1]) != 0)
    return (LOAD_PATH);
  return (CLEAN);
}

int	my_exit(char **args, char ***env)
{
  (void)args;
  (void)env;
  return (EXIT_PROG);
}
