/*
** my_strcmp.c for my str cmp in /home/gaspar_q/rendu/Systeme_Unix/PSU_2014_minishell1
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Fri Jan  9 16:22:09 2015 quentin gasparotto
** Last update Tue Jan 13 10:53:21 2015 quentin gasparotto
*/

#include "../include/minishell.h"

int	my_strcmp(char *ref_str, char *cmp)
{
  int	rank;

  rank = 0;
  while (ref_str[rank] != '\0' && cmp[rank] != '\0')
    {
      if (ref_str[rank] != cmp[rank])
	return (0);
      rank = rank + 1;
    }
  if (ref_str[rank] == '\0' && cmp[rank] == '\0')
    return (2);
  return (1);
}
