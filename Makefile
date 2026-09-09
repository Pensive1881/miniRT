NAME		= miniRT

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
MLX_DIR		= minilibx_macos
MLX_LIB		= $(MLX_DIR)/libmlx.a
INCLUDES	= -Iincludes -I$(MLX_DIR)
LIBS		= -L$(MLX_DIR) -lmlx \
			  -framework OpenGL -framework AppKit -lm

SRCS		= src/main.c \
			  src/mlx_app.c \
			  src/render.c \
			  src/camera.c \
			  src/ray.c \
			  src/sphere.c \
			  src/vec3.c \
			  src/vec3_utils.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(MLX_DIR clean)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re