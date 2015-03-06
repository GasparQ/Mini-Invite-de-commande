/*
** is_in_str.c for check if a char is in a str in /home/gaspar_q/rendu/Systeme_Unix/PSU_2014_minishell1/sources
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Tue Jan 20 17:07:21 2015 quentin gasparotto
** Last update Mon Feb  9 13:40:59 2015 quentin gasparotto
*/

#include "../include/minishell.h"

int	is_in_str(char cmp_char, char *ref_str)
{
  int	rank;

  rank = 0;
  while (ref_str[rank] != '\0')
    {
      if (ref_str[rank] == cmp_char)
	return (1);
      rank = rank + 1;
    }
  return (0);
}
