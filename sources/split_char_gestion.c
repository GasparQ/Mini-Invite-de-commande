/*
** split_char_gestion.c for gestion of all cmd split characteres in /home/gaspar_q/rendu/semestre_2/Systeme_Unix/PSU_2014_minishell2
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Fri Feb 27 15:21:38 2015 quentin gasparotto
** Last update Thu Mar  5 18:14:36 2015 quentin gasparotto
*/

#include "../include/minishell.h"

int	pipe_gestion(t_args **exec_time, t_args **arg, t_shell *my_sh)
{
  int	ret;
  int	(*save)(char *, char **, t_shell *);

  *arg = (*arg)->next;
  if (*arg != NULL && (*arg)->argv != NULL && (*arg)->argv[0] != NULL)
    {
      save = my_sh->fork_cmd;
      my_sh->fork_cmd = &pipe_fork;
      ret = execute_command(my_sh, (*exec_time)->argv);
      my_sh->fork_cmd = save;
      if (ret == ERROR)
	return (BROKEN_PIPE);
      *exec_time = *arg;
    }
  else
    return (UNEXPECT_SPLIT);
  *arg = (*arg)->next;
  return (ret);
}

int	right_red_gestion(t_args **exec_time, t_args **arg, t_shell *my_sh)
{
  int	fd;
  int	flag;

  (void)exec_time;
  (void)my_sh;
  fd = -1;
  if (my_strcmp((*arg)->argv[0], ">>") == 2)
    flag = O_WRONLY | O_APPEND | O_CREAT;
  else
    flag = O_WRONLY | O_CREAT;
  (*arg) = (*arg)->next;
  if (*arg != NULL && (*arg)->argv != NULL && (*arg)->argv[0] != NULL)
    {
      if ((fd = open((*arg)->argv[0], flag, FILE_RIGHT)) == ERROR)
	return (my_strerror(OPEN_ERR));
      if (dup2(fd, 1) == ERROR)
	return (my_strerror(DUP_ERR));
    }
  else
    return (UNEXPECT_SPLIT);
  *arg = (*arg)->next;
  return (fd);
}

int	left_red_gestion(t_args **exec_time, t_args **arg, t_shell *my_sh)
{
  int	fd;

  (void)exec_time;
  (void)my_sh;
  fd = -1;
  *arg = (*arg)->next;
  if (*arg != NULL)
    {
      if (fd != -1)
	close(fd);
      if ((fd = open((*arg)->argv[0], O_RDONLY)) == ERROR)
	return (my_strerror(OPEN_ERR));
      if (dup2(fd, 0) == ERROR)
	return (my_strerror(DUP_ERR));
    }
  else
    return (UNEXPECT_SPLIT);
  *arg = (*arg)->next;
  return (fd);
}

int	double_left_red_gestion(t_args **exec_time,
				t_args **arg, t_shell *my_sh)
{
  int	end;
  int	len;
  char	save_buff[4096];

  *arg = (*arg)->next;
  if (*arg == NULL || (*arg)->argv == NULL || (*arg)->argv[0] == NULL)
    return (UNEXPECT_SPLIT);
  (void)exec_time;
  len = 0;
  while (BUFFSIZE - len > 0)
    {
      my_putstr(">>");
      if ((end = read(1, &my_sh->buff[len], BUFFSIZE - len)) == ERROR)
	return (my_strerror(READ_ERR));
      my_sh->buff[len + end] = '\0';
      my_strcpy(&(my_sh->buff[len]), save_buff);
      (end - 1 >= 0) ? (save_buff[end - 1] = '\0') : 0;
      if (my_strcmp(save_buff, (*arg)->argv[0]) == 2)
	break;
      len += end;
    }
  my_sh->buff[len] = '\0';
  my_sh->fork_cmd = &double_left_fork;
  *arg = (*arg)->next;
  return (CLEAN);
}
