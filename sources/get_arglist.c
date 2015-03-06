/*
** get_arglist.c for function to get a list of all args from cmd line in /home/gaspar_q/rendu/semestre_2/Systeme_Unix/PSU_2014_minishell2
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Mon Feb  9 13:47:05 2015 quentin gasparotto
** Last update Wed Mar  4 20:49:44 2015 quentin gasparotto
*/

#include "../include/minishell.h"

void	split_arg(char *cmd_line, int *rank, int size, char *buff)
{
  int	i;

  i = 0;
  while (i < size)
    {
      buff[i] = cmd_line[(*rank) + i];
      i = i + 1;
    }
  buff[i] = '\0';
}

int	get_split(char *cmd_line, int *rank, t_args *act)
{
  int	size;

  size = 0;
  while (is_in_str(cmd_line[(*rank) + size], CMD_SPLIT) == 1 &&
	 cmd_line[(*rank) + size] != '\0')
    {
      size = size + 1;
    }
  if (cmd_line[(*rank) + size] != '\0' || size > 0)
    {
      if ((act->argv = malloc(sizeof(char *) * 2)) == NULL)
	return (my_strerror(MALLOC_ERR));
      act->argv[1] = NULL;
      if ((act->argv[0] = malloc(sizeof(char) * (size + 1))) == NULL)
	return (my_strerror(MALLOC_ERR));
      split_arg(cmd_line, rank, size, act->argv[0]);
      *rank = (*rank) + size;
      return (CLEAN);
    }
  *rank = (*rank) + size;
  return (ERROR);
}

int		search_cmd(char *cmd_line, int *rank, t_args **arg_list)
{
  t_args	act;

  if ((act.argv = get_args(&cmd_line[*rank], " \t")) == NULL)
    return (ERROR);
  if (act.argv[0] != NULL)
    {
      if (my_put_in_list(arg_list, act) == ERROR)
	return (ERROR);
    }
  while (is_in_str(cmd_line[*rank], CMD_SPLIT) == 0 && cmd_line[*rank] != '\0')
    {
      if (cmd_line[*rank] == '"')
	{
	  *rank = (*rank) + 1;
	  while (cmd_line[*rank] != '"' && cmd_line[*rank] != '\0')
	    *rank = (*rank) + 1;
	}
      else
	*rank = (*rank) + 1;
    }
  return (CLEAN);
}

int		search_split(char *cmd_line, int *rank, t_args **arg_list)
{
  t_args	act;

  if (cmd_line[*rank] != '\0')
    {
      if (get_split(cmd_line, rank, &act) == CLEAN)
	{
	  if (my_put_in_list(arg_list, act) == ERROR)
	    return (ERROR);
	}
    }
  return (CLEAN);
}

int		get_argslist(char *cmd_line, t_args **arg_list)
{
  int		rank;

  *arg_list = NULL;
  rank = 0;
  while (cmd_line[rank] != '\0')
    {
      if (search_cmd(cmd_line, &rank, arg_list) == ERROR)
	return (ERROR);
      if (search_split(cmd_line, &rank, arg_list) == ERROR)
	return (ERROR);
    }
  return (CLEAN);
}
