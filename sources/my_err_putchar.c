/*
** my_err_putchar.c for my err putchar in /home/gaspar_q/rendu/Systeme_Unix/PSU_2014_minishell1/sources
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Mon Jan 12 13:38:52 2015 quentin gasparotto
** Last update Mon Jan 12 16:13:31 2015 quentin gasparotto
*/

#include <unistd.h>

void	my_err_putchar(char c)
{
  write(2, &c, 1);
}
