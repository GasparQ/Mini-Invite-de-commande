/*
** concatenate_len.c for concatenate length of a wordtab in /home/gaspar_q/rendu/semestre_2/Systeme_Unix/PSU_2014_minishell2
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Thu Feb 26 18:12:03 2015 quentin gasparotto
** Last update Thu Feb 26 18:17:52 2015 quentin gasparotto
*/

#include "../include/minishell.h"

int	concatenate_length(char **wordtab)
{
  int	word;
  int	rank;
  int	len;

  len = 0;
  word = 0;
  while (wordtab[word] != NULL)
    {
      rank = 0;
      while (wordtab[word][rank] != '\0')
	rank = rank + 1;
      len += rank;
      word = word + 1;
    }
  return (len);
}
