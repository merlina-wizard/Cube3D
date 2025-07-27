# Makefile - cub3D

NAME    = cub3D
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -DBUFFER_SIZE=1024
INCLUDES = -Iinclude -Iinclude/libft -Iinclude/gnl -Imlx
MLX     = mlx/libmlx.a -lXext -lX11 -lm -lz

SRC = \
	main.c \
	src/init/init.c \
	src/parse/parse_map.c \
	src/parse/validation_map.c \
	src/parse/parse_render.c \
	src/utils/utils.c \
	src/events/events.c \
	src/player/player.c \
	src/render/render_frame.c \
	include/gnl/get_next_line.c \
	include/gnl/get_next_line_utils.c

OBJ = $(SRC:.c=.o)

LIBFT_DIR = include/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx.a

# Colors
GREEN   = \033[0;32m
YELLOW  = \033[1;33m
BLUE    = \033[0;36m
RESET   = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJ)
	@echo "$(BLUE)🔧 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)

$(LIBFT):
	@echo "$(BLUE)📦 Building libft...$(RESET)"
	@make -C $(LIBFT_DIR) > /dev/null

$(MLX_LIB):
	@echo "$(BLUE)📦 Building MLX...$(RESET)"
	@make -C $(MLX_DIR) > /dev/null

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(YELLOW)🧹 Cleaning object files...$(RESET)"
	@rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean > /dev/null
	@make -C $(MLX_DIR) clean > /dev/null

fclean: clean
	@echo "$(YELLOW)🗑️ Removing binary...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean > /dev/null

re: fclean all

.PHONY: all clean fclean re
