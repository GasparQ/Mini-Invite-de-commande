/*
** infinite_io_gestion.c for gestion of infinite redir, pipe, semicolon in /home/gaspar_q/rendu/semestre_2/Systeme_Unix/PSU_2014_minishell2
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Mon Feb 16 10:26:42 2015 quentin gasparotto
** Last update Fri Feb 27 15:54:32 2015 quentin gasparotto
*/

#include "../include/minishell.h"

int	exit_cleanly(int save_io[2], int ret_value, int fd)
{
  if (dup2(save_io[0], 0) == ERROR)
    return (ERROR);
  if (dup2(save_io[1], 1) == ERROR)
    return (ERROR);
  if (fd != -1)
    close(fd);
  return (ret_value);
}

int	resolve_exec_return(int ret, int save_io[2], int *fd, t_shell *my_sh)
{
  if (ret < CLEAN)
    return (exit_cleanly(save_io, ret, *fd));
  else if (ret == LOAD_PATH)
    {
      if (load_path(my_sh->env, &(my_sh->pathes)) == PATH_ERR)
	return (exit_cleanly(save_io, PATH_ERR, *fd));
    }
  else if (ret != CLEAN)
    {
      if (*fd != -1)
	close(*fd);
      (*fd) = ret;
    }
  return (CLEAN);
}

int	(*get_split_func(char *split_arg))(t_args **, t_args **, t_shell *)
{
  int	i;
  int	(*split_func[5])(t_args **, t_args **, t_shell *);
  char	*split_str[5];

  init_split_function(split_str, split_func);
  i = 0;
  while (my_strcmp(split_arg, split_str[i]) != 2 && i < 5)
    {
      i = i + 1;
    }
  if (i == 5)
    return (NULL);
  return (split_func[i]);
}

int	init_vars(int save_io[2], int *fd, t_shell *my_sh)
{
  if ((save_io[0] = dup(0)) == ERROR)
    return (my_strerror(DUP_ERR));
  if ((save_io[1] = dup(1)) == ERROR)
    return (my_strerror(DUP_ERR));
  *fd = -1;
  my_sh->fork_cmd = classic_fork;
  return (CLEAN);
}

int		infinite_split(t_args **arg, t_shell *my_sh)
{
  int		save_io[2];
  int		ret;
  int		fd;
  t_args	*exec_time;
  int		(*split_func)(t_args **, t_args **, t_shell *);

  if (init_vars(save_io, &fd, my_sh) == ERROR)
    return (ERROR);
  if (*arg != NULL && (*arg)->argv != NULL && (*arg)->argv[0] != NULL)
    exec_time = *arg;
  *arg = (*arg)->next;
  while (*arg != NULL && (*arg)->argv[0] != NULL &&
	 is_in_str((*arg)->argv[0][0], CMD_SPLIT))
    {
      if (my_strcmp((*arg)->argv[0], ";") == 2)
	break;
      if ((split_func = get_split_func((*arg)->argv[0])) == NULL)
	return (exit_cleanly(save_io, UNEXPECT_SPLIT, fd));
      ret = split_func(&exec_time, arg, my_sh);
      if ((ret = resolve_exec_return(ret, save_io, &fd, my_sh)) != CLEAN)
	return (ret);
    }
  ret = execute_command(my_sh, exec_time->argv);
  return (exit_cleanly(save_io, ret, fd));
}
