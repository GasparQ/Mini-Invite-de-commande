/*
** execute_command.c for execute send command in /home/gaspar_q/rendu/Systeme_Unix/PSU_2014_minishell1/sources
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Thu Jan  8 16:19:47 2015 quentin gasparotto
** Last update Thu Mar  5 18:07:25 2015 quentin gasparotto
*/

#include "../include/minishell.h"

char	*str_fusion(char *str_one, char *str_two, char between_char)
{
  char	*final_str;
  int	len_one;

  len_one = my_strlen(str_one);
  if ((final_str = malloc(len_one + my_strlen(str_two) + 2)) == NULL)
    {
      return (NULL);
    }
  final_str[len_one + my_strlen(str_two) + 1] = '\0';
  my_strncpy(str_one, final_str, len_one);
  if (str_one[len_one - 1] != between_char)
    {
      final_str[len_one] = between_char;
      my_strncpy(str_two, &final_str[len_one + 1], my_strlen(str_two));
    }
  else
    my_strncpy(str_two, &final_str[len_one], my_strlen(str_two));
  return (final_str);
}

int	check_n_exec(char *entire_path, char **args, t_shell *my_sh)
{
  if (access(entire_path, F_OK) == 0)
    {
      if (access(entire_path, X_OK) == 0)
	{
	  if (my_sh->fork_cmd(entire_path, args, my_sh) == ERROR)
	    return (ERROR);
	  return (1);
	}
      my_err_putstr(entire_path);
      return (my_strerror(RIGHTS));
    }
  return (0);
}

int	check_basic_cmd(t_shell *my_sh, char **args)
{
  int	tell_tale;
  int	which_path;
  char	*entire_path;

  tell_tale = 0;
  which_path = 0;
  if (my_sh->pathes != NULL)
    {
      while (my_sh->pathes[which_path] != NULL && tell_tale == 0)
	{
	  entire_path = str_fusion(my_sh->pathes[which_path], args[0], '/');
	  if (entire_path == NULL)
	    return (my_strerror(MALLOC_ERR));
	  if ((tell_tale = check_n_exec(entire_path, args, my_sh)) == 0)
	    which_path = which_path + 1;
	  free(entire_path);
	}
    }
  if (tell_tale == 0)
    {
      my_err_putstr(args[0]);
      return (my_strerror(NOT_FOUND));
    }
  return (CLEAN);
}

int	check_builtins(char **args, t_shell *my_sh)
{
  char	*builtins[5];
  int	which_builtin;
  int	(*builtins_tab[5])(char **, char ***);

  init_builtins_tab(builtins, builtins_tab, 0);
  which_builtin = 0;
  while (which_builtin < 5 && my_strcmp(args[0], builtins[which_builtin]) != 2)
    {
      which_builtin = which_builtin + 1;
    }
  init_builtins_tab(builtins, builtins_tab, 4);
  if (which_builtin == 5)
    {
      return (NO_BUILT);
    }
  if (my_sh->fork_cmd == &pipe_fork)
    return (pipe_builtins(args, &(my_sh->env), builtins_tab, which_builtin));
  return (builtins_tab[which_builtin](args, &(my_sh->env)));
}

int	execute_command(t_shell *my_sh, char **args)
{
  int	tell_tale;

  tell_tale = check_builtins(args, my_sh);
  if (tell_tale == EXIT_PROG)
    return (EXIT_PROG);
  else if (tell_tale == LOAD_PATH)
    return (LOAD_PATH);
  else if (tell_tale == NO_BUILT)
    {
      tell_tale = check_n_exec(args[0], args, my_sh);
      if (tell_tale == ERROR)
	return (ERROR);
      else if (tell_tale != 1)
	{
	  tell_tale = check_basic_cmd(my_sh, args);
	}
      if (tell_tale == ERROR)
	return (ERROR);
    }
  return (CLEAN);
}
