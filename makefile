CC = gcc
CFLAGS = -Wall -Wextra -Werror
READLINE = -L/Users/taehkwon/.brew/opt/readline/lib -lreadline -I/Users/taehkwon/.brew/opt/readline/include
LIBFT = ./libft/libft.a
RM = rm -f
NAME = minishell

SRCS =	close.c \
		error.c \
		execute_run_utils.c \
		execute.c \
		expand.c \
		free.c \
		ft_cd.c \
		ft_echo.c \
		ft_env.c \
		ft_exit.c \
		ft_export.c \
		ft_pwd.c \
		ft_unset.c \
		get_list.c \
		heredoc.c \
		init.c \
		is_builtin.c \
		libft_plus.c \
		main_utils.c \
		main.c \
		make_node.c \
		pipe_utils.c \
		pipe.c \
		print.c \
		signal.c \
		syntax_error.c \
		token.c \
		type.c	\
		bitmap.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) $(READLINE) $(LIBFT) -o $(NAME) 

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C libft clean
	$(RM) $(OBJS)

fclean: clean
	make -C libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
