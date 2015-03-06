/*
** find_var.c for find an environment variable in /home/gaspar_q/rendu/Systeme_Unix/PSU_2014_minishell1/sources
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Mon Jan 12 14:56:05 2015 quentin gasparotto
** Last update Tue Jan 13 12:22:32 2015 quentin gasparotto
*/

#include "../include/minishell.h"

int	find_env_var(char *search_var, char **env)
{
  int	var;

  var = 0;
  while (env[var] != NULL &&
	 (my_strcmp(search_var, env[var]) != 1 ||
	  env[var][my_strlen(search_var)] != '='))
    {
      var = var + 1;
    }
  return (var);
}
