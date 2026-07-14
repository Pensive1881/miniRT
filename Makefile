NAME		= miniRT

CC			= -Wall -Wextra -Werror
INCLUDES	= -Iincludes

SRCS		= src/main.c
OBJS		= $(SRCS: .c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(OBJS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re