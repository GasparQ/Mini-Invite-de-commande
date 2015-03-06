/*
** free_wordtab.c for free wordtab in /home/gaspar_q/rendu/Systeme_Unix/PSU_2014_minishell1
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Thu Jan  8 15:49:13 2015 quentin gasparotto
** Last update Wed Jan 21 10:37:25 2015 quentin gasparotto
*/

#include "../include/minishell.h"

void	free_wordtab(char **word_tab)
{
  int	word;

  word = 0;
  while (word_tab[word] != NULL)
    {
      free(word_tab[word]);
      word = word + 1;
    }
  free(word_tab);
}
