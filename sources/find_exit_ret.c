/*
** find_exit_ret.c for find exit return value in /home/gaspar_q/rendu/semestre_2/Systeme_Unix/PSU_2014_minishell2
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Fri Feb 27 17:20:37 2015 quentin gasparotto
** Last update Fri Feb 27 17:58:58 2015 quentin gasparotto
*/

#include "../include/minishell.h"

int	extract_nb(char *str)
{
  int	rank;

  rank = 0;
  while (((str[rank] >= '0' && str[rank] <= '9')
	  || str[rank] == '-' || str[rank] == '+')
	 && str[rank] != '\0')
    rank = rank + 1;
  str[rank] = '\0';
  return (my_getnbr(str));
}

int	find_exit_ret(char *last_cmd)
{
  int	rank;

  rank = 0;
  while (last_cmd[rank] != '\0')
    {
      if (last_cmd[rank] == 'e' && my_strcmp("exit", &last_cmd[rank]) == 1)
	{
	  rank = rank + 5;
	  break;
	}
      else
	rank = rank + 1;
    }
  if ((last_cmd[rank] >= '0' && last_cmd[rank] <= '9')
      || last_cmd[rank] == '-' || last_cmd[rank] == '+')
    return (extract_nb(&last_cmd[rank]));
  else
    return (0);
}
