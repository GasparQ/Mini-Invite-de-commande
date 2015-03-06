/*
** every_exec.c for file where each fork func are in in /home/gaspar_q/rendu/semestre_2/Systeme_Unix/PSU_2014_minishell2
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Fri Feb 13 10:15:32 2015 quentin gasparotto
** Last update Thu Mar  5 17:59:41 2015 quentin gasparotto
*/

#include "../include/minishell.h"

int	wait_son()
{
  int	status;

  wait(&status);
  if (WEXITSTATUS(status) > 128)
    return (ERROR);
  return (CLEAN);
}

int	double_left_fork(char *entire_path, char **arg, t_shell *my_sh)
{
  int	tunnel[2];
  pid_t	process_pid;

  if (pipe(tunnel) == ERROR)
    return (my_strerror(PIPE_ERR));
  if (write(tunnel[1], my_sh->buff, my_strlen(my_sh->buff)) == ERROR)
    return (my_strerror(WRT_ERR));
  close(tunnel[1]);
  if ((process_pid = fork()) == ERROR)
    return (my_strerror(FORK_ERR));
  if (process_pid == 0)
    {
      (dup2(tunnel[0], 0) == ERROR) ? exit(my_strerror(DUP_ERR)) : 0;
      close(tunnel[0]);
      (execve(entire_path, arg, my_sh->env) == ERROR) ?	exit(3) : 0;
    }
  else
    {
      if (wait_son() == ERROR)
	return (ERROR);
      close(tunnel[0]);
    }
  return (CLEAN);
}

int	pipe_fork(char *entire_path, char **arg, t_shell *my_sh)
{
  int	new_io[2];
  pid_t	process_pid;

  if (pipe(new_io) == ERROR)
    return (my_strerror(PIPE_ERR));
  if ((process_pid = fork()) == ERROR)
    return (my_strerror(FORK_ERR));
  if (process_pid == 0)
    {
      close(new_io[0]);
      (dup2(new_io[1], 1) == ERROR) ? exit(my_strerror(DUP_ERR)) : 0;
      close(new_io[1]);
      (execve(entire_path, arg, my_sh->env) == ERROR) ?	exit(3) : 0;
    }
  else
    {
      if (wait_son() == ERROR)
	return (ERROR);
      close(new_io[1]);
      if (dup2(new_io[0], 0) == ERROR)
	return (my_strerror(DUP_ERR));
      close(new_io[0]);
    }
  return (CLEAN);
}

int	classic_fork(char *entire_path, char **arg, t_shell *my_sh)
{
  pid_t	process_pid;

  if ((process_pid = fork()) == ERROR)
    return (my_strerror(FORK_ERR));
  if (process_pid == 0)
    {
      if (execve(entire_path, arg, my_sh->env) == ERROR)
	exit(3);
    }
  else
    {
      wait(NULL);
    }
  return (CLEAN);
}
