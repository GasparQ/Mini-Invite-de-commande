/*
** my_strdup.c for my_strdup in /home/gaspar_q/rendu/Piscine_C_J08/ex_01
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Wed Oct  8 09:20:32 2014 quentin gasparotto
** Last update Thu Jan  8 11:41:47 2015 quentin gasparotto
*/

#include "../include/minishell.h"
#include <stdlib.h>

char	*my_strdup(char *src)
{
  int	len;
  int	a;
  char	*dest;

  len = my_strlen(src);
  a = 0;
  if ((dest = malloc(len + 1)) == NULL)
    return (NULL);
  while (src[a] != '\0')
    {
      dest[a] = src[a];
      a = a + 1;
    }
  dest[a] = '\0';
  return (dest);
}
