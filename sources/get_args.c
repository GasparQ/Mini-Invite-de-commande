/*
** get_args.c for file with function to get the arguments from a command line in /home/gaspar_q/rendu/Systeme_Unix/PSU_2014_minishell1
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Thu Jan  8 15:50:36 2015 quentin gasparotto
** Last update Wed Mar  4 20:47:27 2015 quentin gasparotto
*/

#include "../include/minishell.h"

void	suppress_split_char(char *cmd, int *rank, char *split_char)
{
  while (is_in_str(cmd[*rank], split_char) == 1 &&
	 cmd[(*rank) + 1] != '\0')
    {
      (*rank) = (*rank) + 1;
    }
}

int	arg_recognizer(char *cmd, int *rank, int *arg_nb, char *split_char)
{
  if (cmd[*rank] == '"')
    {
      *rank = (*rank) + 1;
      while (cmd[*rank] != '"' && cmd[*rank] != '\0')
	*rank = (*rank) + 1;
      *arg_nb = (*arg_nb) + 1;
      if (cmd[*rank] == '"')
	*rank = (*rank) + 1;
      else
	return (my_strerror(BAD_SYNTHAX));
    }
  else
    {
      while (is_in_str(cmd[*rank], split_char) == 0 && cmd[*rank] != '\0')
	*rank = (*rank) + 1;
      *arg_nb = (*arg_nb) + 1;
      if (cmd[*rank] != '\0')
	*rank = (*rank) + 1;
    }
  return (CLEAN);
}

int	get_arg_nb(char *cmd, char *split_char)
{
  int	rank;
  int	arg_nb;

  if (cmd == NULL)
    return (ERROR);
  rank = 0;
  arg_nb = 0;
  while (cmd[rank] != '\0')
    {
      suppress_split_char(cmd, &rank, split_char);
      if (is_in_str(cmd[rank], CMD_SPLIT) == 1)
	return (arg_nb);
      if (arg_recognizer(cmd, &rank, &arg_nb, split_char) == ERROR)
	return (ERROR);
    }
  return (arg_nb);
}

char	*extract_arg(char *cmd, int *rank, char *split_char)
{
  char	*arg;
  int	i;

  suppress_split_char(cmd, rank, split_char);
  i = 0;
  if (cmd[*rank] == '"')
    {
      *rank = (*rank) + 1;
      while (cmd[(*rank) + i] != '"' && cmd[(*rank) + i] != '\0')
	i = i + 1;
    }
  else
    {
      while (is_in_str(cmd[(*rank) + i], split_char) == 0 &&
	     cmd[(*rank) + i] != '\0')
	i = i + 1;
    }
  if ((arg = malloc(i + 1)) == NULL)
    exit(my_strerror(MALLOC_ERR));
  my_strncpy(&cmd[*rank], arg, i);
  arg[i] = '\0';
  if (cmd[*rank = (*rank) + i] == '"')
    *rank = (*rank) + 1;
  return (arg);
}

char	**get_args(char *cmd, char *split_char)
{
  char	**args;
  int	arg_nb;
  int	arg;
  int	rank;

  if ((arg_nb = get_arg_nb(cmd, split_char)) == ERROR)
    return (NULL);
  if ((args = malloc(sizeof(char *) * (arg_nb + 1))) == NULL)
    exit(my_strerror(MALLOC_ERR));
  args[arg_nb] = NULL;
  arg = 0;
  rank = 0;
  while (arg < arg_nb)
    {
      if ((args[arg] = extract_arg(cmd, &rank, split_char)) == NULL)
	return (NULL);
      arg = arg + 1;
    }
  return (args);
}
