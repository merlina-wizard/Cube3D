NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX = -lmlx -framework OpenGL -framework AppKit

SRC = main.c \
      src/init/init_game.c \
      src/init/init_map.c \
      src/render/draw.c \
      src/render/raycast.c \
      src/player/movement.c \
      src/player/rotation.c \
      src/events/hooks.c \
      src/events/exit.c \
      src/utils/errors.c \
      src/utils/colors.c

OBJ = $(SRC:.c=.o)

INCLUDES = -Iinclude -Ilibft

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a $(MLX) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
