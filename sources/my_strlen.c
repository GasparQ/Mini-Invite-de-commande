/*
** my_strlen.c for my_strlen in /home/gaspar_q/rendu/Piscine_C_J04
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Thu Oct  2 11:25:29 2014 quentin gasparotto
** Last update Mon Feb  9 13:39:25 2015 quentin gasparotto
*/

int	my_strlen(char *str)
{
  int	len;

  len = 0;
  while (str[len] != '\0')
    {
      len = len + 1;
    }
  return (len);
}
