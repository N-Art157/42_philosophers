NAME	= philo
SRCS	= $(shell find . -type f -name "*.c")
OBJS	= $(SRCS:.c=.o)
CC		= cc -Wall -Wextra -Werror -I.

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -pthread

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re