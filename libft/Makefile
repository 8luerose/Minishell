# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 14:11:42 by seojchoi          #+#    #+#              #
#    Updated: 2023/08/12 13:21:14 by seojchoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = \
	ft_putchar_fd.c ft_strmapi.c ft_atoi.c \
	ft_putendl_fd.c ft_strncmp.c ft_bzero.c ft_putnbr_fd.c \
	ft_strnstr.c ft_calloc.c ft_putstr_fd.c ft_strrchr.c ft_isalnum.c \
	ft_split.c ft_strtrim.c ft_isalpha.c  ft_strchr.c ft_substr.c \
	ft_isascii.c ft_strdup.c ft_tolower.c ft_isdigit.c ft_memchr.c ft_striteri.c \
	ft_toupper.c ft_isprint.c ft_memcmp.c ft_strjoin.c ft_itoa.c \
	ft_memcpy.c ft_strlcat.c ft_memmove.c ft_strlcpy.c ft_memset.c ft_strlen.c \
	get_next_line.c
OBJ = $(SRC:.c=.o)
NAME = libft.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar -rc $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^ 

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all