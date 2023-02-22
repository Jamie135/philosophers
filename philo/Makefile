NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

INC =	philo.h

SRCS =	philo.c \
		utils.c \
		init.c \
		eat_sleep_think.c \
		process.c \
		free.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(NAME)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
