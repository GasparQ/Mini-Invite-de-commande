/*
** my_put_ps1.c for my put ps1 in /home/gaspar_q/rendu/Systeme_Unix/PSU_2014_minishell1/sources
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Fri Jan 16 16:25:01 2015 quentin gasparotto
** Last update Fri Jan 16 16:42:24 2015 quentin gasparotto
*/

#include "../include/minishell.h"

void	my_putcolor(char *str, int *rank)
{
  int	rk;

  my_putchar('\e');
  (*rank) = (*rank) + 1;
  rk = 0;
  while (rk < 6 && str[(*rank) + rk] != '\0')
    {
      my_putchar(str[(*rank) + rk]);
      rk = rk + 1;
    }
  *rank = (*rank) + rk - 1;
}

void	my_put_user(char **env)
{
  int	var;

  var = find_env_var("USER", env);
  if (env[var] != NULL)
    my_putstr(&env[var][my_strlen("USER=")]);
}

void	my_put_ps1(char **env)
{
  int	rank;
  int	ps1_var;

  if (env[ps1_var = find_env_var("PS1", env)] != NULL)
    {
      rank = my_strlen("PS1=");
      while (env[ps1_var][rank] != '\0')
	{
	  if (env[ps1_var][rank] == '\\')
	    {
	      rank = rank + 1;
	      if (env[ps1_var][rank] == 'e')
		my_putcolor(env[ps1_var], &rank);
	      else if (env[ps1_var][rank] == 'n')
		my_putchar('\n');
	      else if (env[ps1_var][rank] == 'u')
		my_put_user(env);
	      rank = rank + 1;
	    }
	  else
	    my_putchar(env[ps1_var][rank++]);
	}
    }
  else
    my_putstr("$>");
}
