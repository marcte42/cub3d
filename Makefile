NAME = cub3d

INC = -Iinc

SRCS =	src/cub3d.c \
		src/parse.c \
		src/parse_map.c \
		src/parse_helpers.c \
		src/init.c \
		src/init_textures.c \
		src/init_entities.c \
		src/update.c \
		src/update_player.c \
		src/update_rays.c \
		src/update_entities.c \
		src/events.c \
		src/draw.c \
		src/draw_world.c \
		src/draw_entities.c \
		src/draw_hud.c \
		src/save.c \
		src/errors.c \
		src/helpers.c

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
