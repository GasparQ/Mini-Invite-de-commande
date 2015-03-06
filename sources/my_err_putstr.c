/*
** my_err_putstr.c for my error putstr in /home/gaspar_q/rendu/Systeme_Unix/PSU_2014_minishell1/sources
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Mon Jan 12 13:39:38 2015 quentin gasparotto
** Last update Mon Jan 12 13:40:24 2015 quentin gasparotto
*/

#include "../include/minishell.h"

int	my_err_putstr(char *str)
{
  int	rank;

  rank = 0;
  while (str[rank] != '\0')
    {
      my_err_putchar(str[rank]);
      rank = rank + 1;
    }
  return (rank);
}
