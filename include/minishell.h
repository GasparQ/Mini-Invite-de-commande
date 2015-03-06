/*
** minishell.h for minishell 1 header in /home/gaspar_q/rendu/Systeme_Unix/PSU_2014_minishell1/sources
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Thu Jan  8 10:14:51 2015 quentin gasparotto
** Last update Sat Feb 28 23:57:54 2015 quentin gasparotto
*/

#ifndef	MINISHELL_H_
# define MINISHELL_H_

/*
** Usefull headers
*/

# include <sys/types.h>
# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include <errno.h>

enum	FUNCTION_RETURN
  {
    CLEAN = 0,
    ERROR = -1,
    MALLOC_ERR = -2,
    PATH_ERR = -3,
    ARG_ERR = -4,
    FORK_ERR = -5,
    NO_ENV = -6,
    EXIT_PROG = -7,
    CD_ERR = -8,
    RIGHTS = -9,
    NOT_FOUND = -10,
    SET_ENV_USAGE = -11,
    NO_PATH = -12,
    NO_VAR = -13,
    UNSETENV_USAGE = -14,
    NO_HOME = -15,
    BAD_SYNTHAX = -16,
    BAD_ENV_OPTION = -17,
    BAD_FLAGS = -18,
    EXEC_FAIL = -19,
    PIPE_ERR = -20,
    DUP_ERR = -21,
    UNEXPECT_SPLIT = -22,
    OPEN_ERR = -23,
    UNEXPECT_NEW_LINE = -24,
    WRT_ERR = -25,
    READ_ERR = -26,
    BROKEN_PIPE = -27
  };

enum	START_N_STOP
  {
    STOP,
    START
  };

# define BUFFSIZE	4096
# define LOAD_PATH	1
# define NO_BUILT	2

# define END_FLAG_SRCH	1

# define CMD_SPLIT	";|><"
# define FILE_RIGHT	(S_IRUSR + S_IWUSR + S_IRGRP + S_IROTH)

/*
** Structures
*/

typedef struct	s_args
{
  char		**argv;
  struct s_args	*next;
}		t_args;

typedef struct	s_shell
{
  char		**pathes;
  char		**env;
  char		**args;
  char		buff[4097];
  char		cmd[4097];
  int		(*fork_cmd)(char *, char **, struct s_shell *);
}		t_shell;

/*
** Prototypes
*/

/*
**	find_exit_ret.c
*/

int	find_exit_ret(char *last_cmd);

/*
**	change_old_pwd.c
*/

int	change_old_pwd(char **env, char *pwd);

/*
**	change_previous.c
*/

int	change_previous(char ***env);

/*
**	pipe_builtins.c
*/

int	pipe_builtins(char **args, char ***env,
		      int (*builtins_tab[5])(char **, char ***),
		      int which_builtin);

/*
**	list_fn.c
*/

int	my_put_in_list(t_args **my_list, t_args data);
void	free_my_list(t_args *my_list);

/*
**	get_arglist.c
*/

int	get_argslist(char *cmd_line, t_args **arg_list);

/*
**	load_path.c
*/

int	load_path(char **env, char ***pathes);

/*
**	infinite_gestion.c
*/

int	infinite_split(t_args **arg, t_shell *my_sh);

int	pipe_gestion(t_args **exec_time, t_args **arg, t_shell *my_sh);
int	right_red_gestion(t_args **exec_time, t_args **arg, t_shell *my_sh);
int	left_red_gestion(t_args **exec_time, t_args **arg, t_shell *my_sh);
int	double_left_red_gestion(t_args **exec_time, t_args **arg,
				t_shell *my_sh);

/*
**	every_exec.c
*/

int	double_left_fork(char *entire_path, char **arg, t_shell *my_sh);
int	pipe_fork(char *entire_path, char **arg, t_shell *my_sh);
int	classic_fork(char *entire_path, char **arg, t_shell *my_sh);

/*
**	is_in_str.c
*/

int	is_in_str(char cmp_char, char *ref_str);


/*
**	my_put_ps1.c
*/

void	my_put_ps1(char **env);

/*
**	resolve_home.c
*/

int	resolve_home(char **args, char **env, int rank);
int	resolve_pwd(char **args, char **env);

/*
**	load_root_dir.c
*/

int	load_root(char ***env);

/*
**	init_tabs.c
*/

void	init_builtins_tab(char **builtins,
			   int (**builstins_tab)(char **, char ***), int mode);
void	init_err_mess(char **err_mess);
void	init_err_tab(int *err_tab);
void	init_split_function(char **spit_str, int (**split_func)(t_args **,
								t_args **,
							        t_shell *));

/*
**	env.c
*/

int	get_nb_of_var(char **wordtab);
int	realloc_env(char **env, char ***new_env, int new_size);

/*
**	builtins.c
*/

int	change_directory(char **args, char ***env);
int	env_builtin(char **args, char ***env);
int	set_environment(char **args, char ***env);
int	unset_environment(char **args, char ***env);
int	my_exit(char **args, char ***env);

/*
**	error.c
*/

int	my_strerror(int error);

/*
**	execute_command.c
*/

char	*str_fusion(char *str_one, char *str_two, char between_char);
int	execute_command(t_shell *my_sh, char **args);
int	check_n_exec(char *entire_path, char **args, t_shell *my_sh);

/*
**	get_args.c
*/

char	**get_args(char *cmd, char* split_char);

/*
**	free_wordtab.c
*/

void	free_wordtab(char **wordtab);

/*
**	my_realloc.c
*/

char	**my_realloc_wordtab(char **src, int size);

/*
**	ask_usr.c
*/

int	ask_usr(t_shell *my_sh);

/*
**	find_var.c
*/

int	find_env_var(char *search_var, char **env);

/*
**	lib
*/

void	my_putchar(char c);
void	my_strcpy(char *src, char *dest);
int	my_getnbr(char *str);
int	my_putstr(char *str);
void	my_put_nbr(int nb);
int	my_strlen(char *str);
void	my_strncpy(char *src, char *dest, int n);
char	*my_strdup(char *str);
int	my_strcmp(char *ref_str, char *cmp);
int	my_err_putstr(char *str);
void	my_err_putchar(char c);

#endif /* !MINISHELL_H_ */
