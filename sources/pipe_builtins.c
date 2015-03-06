/*
** pipe_builtins.c for pipe builtins in /home/gaspar_q/rendu/semestre_2/Systeme_Unix/PSU_2014_minishell2
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Thu Feb 26 18:46:06 2015 quentin gasparotto
** Last update Thu Mar  5 18:13:35 2015 quentin gasparotto
*/

#include "../include/minishell.h"

int	pipe_builtins(char **args, char ***env,
		      int (*builtins_tab[5])(char **, char ***),
		      int which_builtin)
{
  int	pipefd[2];
  int	save;
  int	ret;

  if ((save = dup(1)) == ERROR)
    return (my_strerror(DUP_ERR));
  if (pipe(pipefd) == ERROR)
    return (my_strerror(PIPE_ERR));
  if (dup2(pipefd[1], 1) == ERROR)
    return (my_strerror(DUP_ERR));
  close(pipefd[1]);
  ret = builtins_tab[which_builtin](args, env);
  if (dup2(pipefd[0], 0) == ERROR)
    return (my_strerror(DUP_ERR));
  close(pipefd[0]);
  if (dup2(save, 1) == ERROR)
    return (my_strerror(DUP_ERR));
  return (ret);
}
