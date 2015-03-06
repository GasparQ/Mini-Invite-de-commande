/*
** my_strncpy.c for my strncpy in /home/gaspar_q/rendu/Systeme_Unix/PSU_2014_minishell1/sources
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Thu Jan  8 11:17:31 2015 quentin gasparotto
** Last update Thu Jan  8 11:18:42 2015 quentin gasparotto
*/

#include "../include/minishell.h"

void	my_strncpy(char *src, char *dest, int n)
{
  int	i;

  i = 0;
  while (i < n)
    {
      dest[i] = src[i];
      i = i + 1;
    }
}
