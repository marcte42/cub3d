NAME = cub3d

INC = -Iinc

SRCS =	src/cub3d.c \
		src/parser.c \
		src/update_player.c \
		src/events.c \
		src/draw.c \
		src/raycast.c

CC = gcc

FLAGS = -Wall -Wextra -Werror

LIBS = lib/libft.a libmlx.dylib

OBJS = $(SRCS:.c=.o)

all : $(NAME)

.c.o:
	$(CC) $(INC) -c $<  -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -framework OpenGL -framework AppKit -o $(NAME) $(OBJS) $(LIBS)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

run : re
	./$(NAME)

.phony: all clean fclean re run
