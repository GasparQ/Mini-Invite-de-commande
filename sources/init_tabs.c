/*
** init_tabs.c for init tabs in /home/gaspar_q/rendu/Systeme_Unix/PSU_2014_minishell1/sources
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Fri Jan  9 15:04:21 2015 quentin gasparotto
** Last update Fri Feb 27 15:20:33 2015 quentin gasparotto
*/

#include "../include/minishell.h"

void	init_builtins_tab(char **builtins,
			   int (*builtins_tab[5])(char **, char ***), int mode)
{
  if (mode == 0)
    {
      builtins[0] = my_strdup("cd");
      builtins[1] = my_strdup("setenv");
      builtins[2] = my_strdup("unsetenv");
      builtins[3] = my_strdup("env");
      builtins[4] = my_strdup("exit");
      builtins_tab[0] = &change_directory;
      builtins_tab[1] = &set_environment;
      builtins_tab[2] = &unset_environment;
      builtins_tab[3] = &env_builtin;
      builtins_tab[4] = &my_exit;
    }
  else
    {
      while (mode >= 0)
	{
	  free(builtins[mode]);
	  mode = mode - 1;
	}
    }
}

void	init_err_mess(char **err_mess)
{
  err_mess[0] = "Malloc error\n";
  err_mess[1] = "Error when loading the PATH environment variable\n";
  err_mess[2] = "Error when getting the arguments\n";
  err_mess[3] = "Impossible to create a son process\n";
  err_mess[4] = "No environment\n";
  err_mess[5] = "Error when changing directory\n";
  err_mess[6] = ": Permission denied\n";
  err_mess[7] = ": Command not found\n";
  err_mess[8] = "setenv [NAME] [VALUE] [OVERWRITE]\n";
  err_mess[9] = "Can't exec command, PATH variable can't be load\n";
  err_mess[10] = "No such environment variable\n";
  err_mess[11] = "unsetenv [NAME]\n";
  err_mess[12] = "Can't reach HOME var, don't use '~' character\n";
  err_mess[13] = "Bad synthax\n";
  err_mess[14] = "Bad option on env\n";
  err_mess[15] = "You attempt to use bad flags\n";
  err_mess[16] = "Error when executing the command\n";
  err_mess[17] = "Error when creating pipe\n";
  err_mess[18] = "Error when associate input/output\n";
  err_mess[19] = "Unexpected command splitter\n";
  err_mess[20] = "No such file\n";
  err_mess[21] = "Synthax error, unexpected newline\n";
  err_mess[22] = "Error whith write\n";
  err_mess[23] = "Error when reading\n";
  err_mess[24] = "Broken pipe\n";
}

void	init_err_tab(int *err_tab)
{
  err_tab[0] = MALLOC_ERR;
  err_tab[1] = PATH_ERR;
  err_tab[2] = ARG_ERR;
  err_tab[3] = FORK_ERR;
  err_tab[4] = NO_ENV;
  err_tab[5] = CD_ERR;
  err_tab[6] = RIGHTS;
  err_tab[7] = NOT_FOUND;
  err_tab[8] = SET_ENV_USAGE;
  err_tab[9] = NO_PATH;
  err_tab[10] = NO_VAR;
  err_tab[11] = UNSETENV_USAGE;
  err_tab[12] = NO_HOME;
  err_tab[13] = BAD_SYNTHAX;
  err_tab[14] = BAD_ENV_OPTION;
  err_tab[15] = BAD_FLAGS;
  err_tab[16] = EXEC_FAIL;
  err_tab[17] = PIPE_ERR;
  err_tab[18] = DUP_ERR;
  err_tab[19] = UNEXPECT_SPLIT;
  err_tab[20] = OPEN_ERR;
  err_tab[21] = UNEXPECT_NEW_LINE;
  err_tab[22] = WRT_ERR;
  err_tab[23] = READ_ERR;
  err_tab[24] = BROKEN_PIPE;
}

void	init_split_function(char **split_str, int (**split_func)(t_args **,
								 t_args **,
								 t_shell *))
{
  split_str[0] = ">";
  split_func[0] = &right_red_gestion;
  split_str[1] = ">>";
  split_func[1] = &right_red_gestion;
  split_str[2] = "<";
  split_func[2] = &left_red_gestion;
  split_str[3] = "|";
  split_func[3] = &pipe_gestion;
  split_str[4] = "<<";
  split_func[4] = &double_left_red_gestion;
}
