NAME		= miniRT

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -std=gnu17
UNAME_S		:= $(shell uname -s)

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

ifeq ($(UNAME_S),Darwin)
MLX_DIR		= minilibx_macos
MLX_LIB		= $(MLX_DIR)/libmlx.a
INCLUDES	= -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR)
LIBS		= -L$(MLX_DIR) -lmlx \
			  -framework OpenGL -framework AppKit -lm
else
MLX_DIR		?= minilibx-linux
MLX_LIB		= $(MLX_DIR)/libmlx.a
INCLUDES	= -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR)
LIBS		= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
endif

SRCS		= src/main.c \
			  src/parse_values.c \
			  src/parse_elements.c \
			  src/parse_scene.c \
			  src/mlx_app.c \
			  src/render.c \
			  src/lighting.c \
			  src/camera.c \
			  src/ray.c \
			  src/sphere.c \
			  src/vec3.c \
			  src/vec3_utils.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(MLX_LIB) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
