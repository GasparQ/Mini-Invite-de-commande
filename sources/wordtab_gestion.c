/*
** env.c for env file in /home/gaspar_q/rendu/Systeme_Unix/PSU_2014_minishell1/sources
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Mon Jan 12 17:09:02 2015 quentin gasparotto
** Last update Wed Jan 21 10:37:24 2015 quentin gasparotto
*/

#include "../include/minishell.h"

void	show_wordtab(char **wt)
{
  int	wrd;

  wrd = 0;
  while (wt[wrd] != NULL)
    {
      my_putstr(wt[wrd]);
      my_putchar('\n');
      wrd = wrd + 1;
    }
}

int	get_nb_of_var(char **wordtab)
{
  int	nb_of_var;

  nb_of_var = 0;
  while (wordtab[nb_of_var] != NULL)
    {
      nb_of_var = nb_of_var + 1;
    }
  return (nb_of_var);
}

int	realloc_env(char **env, char ***new_env, int new_size)
{
  int	last_arg;

  if (((*new_env) = malloc(sizeof(char *) * new_size)) == NULL)
    return (my_strerror(MALLOC_ERR));
  (*new_env)[new_size - 1] = NULL;
  last_arg = 0;
  while (env[last_arg] != NULL)
    {
      if (((*new_env)[last_arg] = my_strdup(env[last_arg])) == NULL)
	{
	  free(*new_env);
	  return (my_strerror(MALLOC_ERR));
	}
      last_arg = last_arg + 1;
    }
  return (last_arg);
}
