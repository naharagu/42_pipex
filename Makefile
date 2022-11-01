CC		= gcc

LIBFT	= ./libft

CFLAGS	= -Wall -Wextra -Werror -I$(LIBFT)

SRCS	= main.c check_errors.c

NAME	= pipex

OBJS	= ${SRCS:%.c=%.o}

$(NAME): $(OBJS)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) -L $(LIBFT) -lft -o $@ $^

all: $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
