/*
** resolve_home.c for resolve home when there is tilde in /home/gaspar_q/rendu/Systeme_Unix/PSU_2014_minishell1/sources
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Wed Jan 14 12:03:24 2015 quentin gasparotto
** Last update Wed Mar  4 20:50:47 2015 quentin gasparotto
*/

#include "../include/minishell.h"

int	resolve_home(char **args, char **env, int rank)
{
  int	var;
  char	*new_str;

  var = find_env_var("HOME", env);
  if (env[var] == NULL)
    {
      return (my_strerror(NO_HOME));
    }
  if ((new_str = str_fusion(&env[var][5], &args[rank][1], '/')) == NULL)
    return (my_strerror(MALLOC_ERR));
  free(args[rank]);
  args[rank] = new_str;
  return (CLEAN);
}

char	*resolve_parent(char *new_pwd)
{
  int	len;
  char	*parent;

  len = my_strlen(new_pwd);
  while (new_pwd[len] != '/' && len > 0)
    {
      len = len - 1;
    }
  if (len == 0)
    {
      return (new_pwd);
    }
  if ((parent = malloc(len + 1)) == NULL)
    return (new_pwd);
  my_strncpy(new_pwd, parent, len);
  parent[len] = '\0';
  free(new_pwd);
  return (parent);
}

int	find_pwd_from_pathes(char **args, char **new_pwd)
{
  char	**every_path;
  int	which_path;
  char	*transition;

  if ((every_path = get_args(args[1], "/")) == NULL)
    return (CLEAN);
  which_path = 0;
  while (every_path[which_path] != NULL)
    {
      if (my_strcmp(every_path[which_path], "..") == 2)
	*new_pwd = resolve_parent(*new_pwd);
      else if (my_strcmp(every_path[which_path], ".") == 0)
	{
	  transition = str_fusion(*new_pwd, every_path[which_path], '/');
	  if (transition == NULL)
	    return (my_strerror(MALLOC_ERR));
	  free(*new_pwd);
	  *new_pwd = transition;
	}
      which_path = which_path + 1;
    }
  free_wordtab(every_path);
  return (CLEAN);
}

int	resolve_first_directory(char **new_pwd)
{
  char	*transition;

  if (my_strcmp(*new_pwd, "PWD=") == 2)
    {
      if ((transition = str_fusion(*new_pwd, "", '/')) == NULL)
	return (my_strerror(MALLOC_ERR));
      free(*new_pwd);
      *new_pwd = transition;
    }
  return (CLEAN);
}

int	resolve_pwd(char **args, char **env)
{
  int	var;
  char	*new_pwd;

  var = find_env_var("PWD", env);
  if (env[var] == NULL)
    return (ERROR);
  if (change_old_pwd(env, env[var]) == ERROR)
    return (ERROR);
  if (args[1][0] == '/')
    {
      if ((new_pwd = my_strdup("PWD=")) == NULL)
	return (ERROR);
    }
  else
    {
      if ((new_pwd = my_strdup(env[var])) == NULL)
	return (my_strerror(MALLOC_ERR));
    }
  if (find_pwd_from_pathes(args, &new_pwd) == ERROR)
    return (ERROR);
  if (resolve_first_directory(&new_pwd) == ERROR)
    return (ERROR);
  free(env[var]);
  env[var] = new_pwd;
  return (CLEAN);
}
