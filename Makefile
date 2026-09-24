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
# Keep the project-local Linux MiniLibX path for another machine/device.
# If that folder is not present, fall back to the system install.
MLX_DIR		?= minilibx-linux
ifneq ($(wildcard $(MLX_DIR)/libmlx.a),)
MLX_LIB		= $(MLX_DIR)/libmlx.a
INCLUDES	= -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR)
LIBS		= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
else
MLX_DIR		= /usr/local
MLX_LIB		= /usr/local/lib/libmlx.a
INCLUDES	= -Iincludes -I$(LIBFT_DIR) -I/usr/local/include
LIBS		= -L/usr/local/lib -lmlx -lXext -lX11 -lm
endif
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
			  src/objects.c \
			  src/sphere.c \
			  src/vec3.c \
			  src/plane_stub.c \
			  src/vec3_utils.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(MLX_LIB) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

$(MLX_LIB):
	@true

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	if [ -f "$(MLX_DIR)/Makefile" ]; then $(MAKE) -C $(MLX_DIR) clean; fi
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
