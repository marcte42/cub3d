# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/17 22:01:09 by marc              #+#    #+#              #
#    Updated: 2021/04/10 13:53:57 by marcte           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror

SRC =	./libft/ft_isalnum.c	\
		./libft/ft_isalpha.c	\
		./libft/ft_isascii.c	\
		./libft/ft_isdigit.c	\
		./libft/ft_isprint.c	\
		./libft/ft_onlydigit.c	\
		./libft/ft_strlen.c		\
		./libft/ft_tolower.c	\
		./libft/ft_toupper.c	\
		./libft/ft_strcpy.c		\
		./libft/ft_strncpy.c	\
		./libft/ft_strlcpy.c	\
		./libft/ft_strcat.c		\
		./libft/ft_strlcat.c	\
		./libft/ft_strdup.c		\
		./libft/ft_strcmp.c		\
		./libft/ft_strncmp.c	\
		./libft/ft_atoi.c		\
		./libft/ft_isspace.c	\
		./libft/ft_memset.c		\
		./libft/ft_bzero.c		\
		./libft/ft_memcpy.c		\
		./libft/ft_strchr.c		\
		./libft/ft_strrchr.c	\
		./libft/ft_memccpy.c	\
		./libft/ft_memcmp.c		\
		./libft/ft_memmove.c	\
		./libft/ft_memchr.c		\
		./libft/ft_strnstr.c	\
		./libft/ft_calloc.c		\
		./libft/ft_itoa.c		\
		./libft/ft_strjoin.c	\
		./libft/ft_split.c		\
		./libft/ft_putchar_fd.c	\
		./libft/ft_putstr_fd.c	\
		./libft/ft_putnbr_fd.c	\
		./libft/ft_putendl_fd.c	\
		./libft/ft_strtrim.c	\
		./libft/ft_substr.c		\
		./libft/ft_strmapi.c	\
		./libft/ft_lstnew.c		\
		./libft/ft_lstadd_front.c	\
		./libft/ft_lstsize.c	\
		./libft/ft_lstlast.c	\
		./libft/ft_lstadd_back.c	\
		./libft/ft_lstdelone.c	\
		./libft/ft_lstclear.c	\
		./libft/ft_lstiter.c	\
		./libft/ft_lstmap.c		\
		./get_next_line/get_next_line.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ./mlx/ all
	cp ./mlx/libmlx.a .
	ar rc $(NAME) $(OBJ)

clean:
	$(MAKE) -C ./mlx/ clean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f libmlx.a

re: fclean all

.PHONY: all clean fclean re
