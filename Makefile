NAME = cub3d

SRCS =	main.c \
		parser.c

CC = gcc

FLAGS = -Wall -Wextra -Werror -framework OpenGL -framework AppKit

INCLUDES = lib/libft.a libmlx.dylib

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(INCLUDES)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

run : re
	./$(NAME)

.phony: all clean fclean re run
