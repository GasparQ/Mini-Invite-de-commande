/*
** my_strcpy.c for my strcpy in /home/gaspar_q/rendu/semestre_2/Systeme_Unix/PSU_2014_minishell2
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Fri Feb 27 14:50:58 2015 quentin gasparotto
** Last update Fri Feb 27 14:52:22 2015 quentin gasparotto
*/

#include "../include/minishell.h"

void	my_strcpy(char *src, char *dest)
{
  int	rank;

  rank = 0;
  while (src[rank] != '\0')
    {
      dest[rank] = src[rank];
      rank = rank + 1;
    }
  dest[rank] = '\0';
}
