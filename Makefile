NAME = cub3d

INC = -I./inc

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

CFLAGS= -Wall -Wextra -Werror $(INC) -O3

LIBS = -L./lib -lft -lmlx -lXext -lX11 -lm -lbsd

OBJS = $(SRCS:.c=.o)

all : $(NAME)

.c.o:
	$(CC) $(INC) -c $<  -o $@

$(NAME): $(OBJS)
	$(MAKE) -C ./lib/ all
	$(CC) -o $(NAME) $(OBJS) $(LIBS)
clean :
	$(MAKE) -C ./lib/ clean
	rm -rf $(OBJS)

fclean : clean
	$(MAKE) -C ./lib/ fclean
	rm -rf $(NAME)

re : fclean all

.phony: all clean fclean re 
