/*
** my_realloc.c for realloc in /home/gaspar_q/rendu/Systeme_Unix/PSU_2014_minishell1/sources
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Thu Jan  8 11:24:23 2015 quentin gasparotto
** Last update Thu Jan  8 11:41:25 2015 quentin gasparotto
*/

#include "../include/minishell.h"

char	**my_realloc_wordtab(char **src, int size)
{
  char	**word_tab;
  int	var;

  if ((word_tab = malloc(sizeof(char *) * size)) == NULL)
    return (NULL);
  word_tab[size - 1] = NULL;
  var = 0;
  while (var < size - 1)
    {
      word_tab[var] = src[var];
      var = var + 1;
    }
  free(src);
  return (word_tab);
}
