/*
** list_fn.c for list functions in /home/gaspar_q/rendu/semestre_2/Systeme_Unix/PSU_2014_minishell2
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Mon Feb  9 13:53:14 2015 quentin gasparotto
** Last update Fri Feb 27 16:00:56 2015 quentin gasparotto
*/

#include "../include/minishell.h"

int		my_put_in_list(t_args **my_list, t_args data)
{
  t_args	*elem;
  t_args	*tmp;

  if ((elem = malloc(sizeof(*elem))) == NULL)
    return (my_strerror(MALLOC_ERR));
  elem->argv = data.argv;
  elem->next = NULL;
  tmp = *my_list;
  if (tmp != NULL)
    {
      while (tmp->next != NULL)
	tmp = tmp->next;
      tmp->next = elem;
    }
  else
    {
      *my_list = elem;
    }
  return (CLEAN);
}

void		my_show_list(t_args *my_list)
{
  t_args	*tmp;

  tmp = my_list;
  while (tmp != NULL)
    {
      my_putchar('\n');
      tmp = tmp->next;
    }
}

void		free_my_list(t_args *my_list)
{
  t_args	*tmp;

  tmp = my_list;
  while (my_list != NULL)
    {
      tmp = tmp->next;
      free_wordtab(my_list->argv);
      free(my_list);
      my_list = tmp;
    }
}
