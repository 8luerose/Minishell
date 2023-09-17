CC = cc
CFLAGS = -Wall -Wextra -Werror
READLINE = -L/Users/$(USER)/.brew/opt/readline/lib -lreadline
LIBFT = ./libft/libft.a
RM = rm -f
NAME = minishell

SRCS =	close.c \
		error.c \
		execute_utils.c \
		execute_run.c \
		execute_main.c \
		expand_1.c \
		expand_2.c \
		expand_3.c \
		expand_4.c \
		free.c \
		ft_cd.c \
		ft_cd_utils.c \
		ft_echo.c \
		ft_env.c \
		ft_exit.c \
		ft_exit_utils.c \
		ft_export1.c \
		ft_export2.c \
		ft_pwd.c \
		ft_unset.c \
		get_list.c \
		get_list_utils.c \
		heredoc.c \
		heredoc_utils.c \
		init.c \
		is_builtin.c \
		libft_plus.c \
		main_utils.c \
		main.c \
		make_node.c \
		pipe_utils1.c \
		pipe_utils2.c \
		pipe.c \
		signal.c \
		syntax_error.c \
		token.c \
		token_utils.c \
		type.c	\
		bitmap.c

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -I/opt/homebrew/opt/readline/include -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) $(READLINE) $(LIBFT) -o $(NAME) 

clean:
	make -C libft clean
	$(RM) $(OBJS)

fclean: clean
	make -C libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
