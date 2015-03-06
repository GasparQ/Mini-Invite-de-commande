/*
** ask_usr.c for ask command to usr in /home/gaspar_q/rendu/Systeme_Unix/PSU_2014_minishell1/sources
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Thu Jan  8 12:46:00 2015 quentin gasparotto
** Last update Thu Mar  5 17:51:25 2015 quentin gasparotto
*/

#include "../include/minishell.h"

int	next_cmd(t_args **arg)
{
  if (*arg != NULL)
    return (CLEAN);
  while (*arg != NULL &&
	 (*arg)->argv != NULL &&
	 (*arg)->argv[0] != NULL &&
	 (*arg)->argv[0][0] != ';')
    {
      *arg = (*arg)->next;
    }
  if (*arg == NULL || (*arg)->argv == NULL || (*arg)->argv[0] == NULL)
    return (CLEAN);
  if (my_strcmp((*arg)->argv[0], ";") != 2)
    my_strerror(UNEXPECT_SPLIT);
  return (CLEAN);
}

int		resolve_cmd(t_shell *my_sh)
{
  t_args	*my_list;
  t_args	*tmp;
  int		ret;

  ret = CLEAN;
  if (get_argslist(my_sh->cmd, &my_list) == ERROR)
    return (CLEAN);
  tmp = my_list;
  while (tmp != NULL && tmp->argv != NULL && tmp->argv[0] != NULL)
    {
      if ((ret = infinite_split(&tmp, my_sh)) == EXIT_PROG)
	break;
      else if (ret == LOAD_PATH)
	{
	  if (load_path(my_sh->env, &(my_sh->pathes)) == PATH_ERR)
	    return (my_strerror(PATH_ERR));
	}
      else if (ret < CLEAN)
	if (my_strerror(ret) == ERROR &&
	    (ret = next_cmd(&tmp)) == ERROR)
	  break;
      (tmp != NULL) ? (tmp = tmp->next) : 0;
    }
  free_my_list(my_list);
  return (ret);
}

int		ask_usr(t_shell *my_sh)
{
  int		end;

  my_sh->pathes = NULL;
  if (load_path(my_sh->env, &(my_sh->pathes)) == PATH_ERR)
    return (PATH_ERR);
  while (42)
    {
      my_put_ps1(my_sh->env);
      if ((end = read(0, my_sh->cmd, 4096)) == ERROR)
	return (my_strerror(READ_ERR));
      if (end == 0 || my_sh->cmd[0] == ERROR)
	{
	  (my_sh->pathes != NULL) ? (free_wordtab(my_sh->pathes)) : 0;
	  return (CLEAN);
	}
      (end > 0 && my_sh->cmd[end - 1] == '\n') ?
	(my_sh->cmd[end - 1] = '\0') : (my_sh->cmd[end] = '\0');
      if ((end = resolve_cmd(my_sh)) == EXIT_PROG || end == ERROR)
	{
	  if (my_sh->pathes != NULL)
	    free_wordtab(my_sh->pathes);
	  return (end);
	}
    }
  return (CLEAN);
}
