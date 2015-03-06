/*
** minishell.c for main function file in /home/gaspar_q/rendu/Systeme_Unix/PSU_2014_minishell1/sources
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Thu Jan  8 10:14:23 2015 quentin gasparotto
** Last update Fri Feb 27 17:35:09 2015 quentin gasparotto
*/

#include "../include/minishell.h"

int		main(int ac, char **av, char **env)
{
  t_shell	my_sh;
  int		var;
  int		ret;

  (void)ac;
  (void)av;
  my_sh.buff[0] = '\0';
  ret = CLEAN;
  var = get_nb_of_var(env);
  if (realloc_env(env, &(my_sh.env), var + 1) == MALLOC_ERR)
    return (my_strerror(MALLOC_ERR));
  if (load_root(&(my_sh.env)) == ERROR)
    return (ERROR);
  if (ask_usr(&my_sh) == EXIT_PROG)
    ret = find_exit_ret(my_sh.cmd);
  if (my_sh.env != NULL)
    free_wordtab(my_sh.env);
  return (ret);
}
