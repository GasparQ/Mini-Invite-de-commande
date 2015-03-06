/*
** error.c for error gestion file in /home/gaspar_q/rendu/Systeme_Unix/PSU_2014_minishell1/sources
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Thu Jan  8 16:53:53 2015 quentin gasparotto
** Last update Thu Feb 26 17:10:00 2015 quentin gasparotto
*/

#include "../include/minishell.h"

int	my_strerror(int error)
{
  int	err_tab[25];
  char	*err_mess[25];
  int	which_err;

  init_err_tab(err_tab);
  init_err_mess(err_mess);
  which_err = 0;
  while (which_err < 25)
    {
      if (err_tab[which_err] == error)
	my_err_putstr(err_mess[which_err]);
      which_err = which_err + 1;
    }
  return (ERROR);
}
