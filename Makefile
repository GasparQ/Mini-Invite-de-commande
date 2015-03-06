##
## Makefile for minishell 1 makefile in /home/gaspar_q/rendu/Systeme_Unix/PSU_2014_minishell1
## 
## Made by quentin gasparotto
## Login   <gaspar_q@epitech.net>
## 
## Started on  Thu Jan  8 10:05:38 2015 quentin gasparotto
## Last update Fri Feb 27 17:34:05 2015 quentin gasparotto
##

SRCS=	./sources/minishell.c \
	./sources/my_putchar.c \
	./sources/my_put_nbr.c \
	./sources/my_getnbr.c \
	./sources/my_putstr.c \
	./sources/my_strlen.c \
	./sources/my_realloc.c \
	./sources/my_strdup.c \
	./sources/my_err_putstr.c \
	./sources/my_err_putchar.c \
	./sources/my_strncpy.c \
	./sources/my_strcmp.c \
	./sources/ask_usr.c \
	./sources/free_wordtab.c \
	./sources/get_args.c \
	./sources/execute_command.c \
	./sources/error.c \
	./sources/init_tabs.c \
	./sources/load_root_dir.c \
	./sources/builtins.c \
	./sources/find_var.c \
	./sources/wordtab_gestion.c \
	./sources/resolve_home.c \
	./sources/my_put_ps1.c \
	./sources/is_in_str.c \
	./sources/get_arglist.c \
	./sources/list_fn.c \
	./sources/every_exec.c \
	./sources/infinite_io_gestion.c \
	./sources/load_path.c \
	./sources/concatenate_len.c \
	./sources/pipe_builtins.c \
	./sources/my_strcpy.c \
	./sources/split_char_gestion.c \
	./sources/change_old_pwd.c \
	./sources/change_previous.c \
	./sources/find_exit_ret.c \

OBJS=	$(SRCS:.c=.o)

CC=	gcc -g

RM=	rm -f

NAME=	mysh


CFLAGS=	-Wall -Wextra

$(NAME):	$(OBJS)
	$(CC) $(OBJS) -o $(NAME)

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
