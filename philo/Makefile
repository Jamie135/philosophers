# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/10 14:21:26 by pbureera          #+#    #+#              #
#    Updated: 2023/02/24 15:14:24 by pbureera         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = ./philo.c \
		./routine.c \
		./eat.c \
		./init.c \
		./start.c \
		./time_functions.c \
		./forks.c \
		./stop.c \
		./utils.c

GCC = cc
FLAGS = -g -pthread -Wextra -Wall -Werror #-fsanitize=thread
OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	${GCC} ${FLAGS} ${OBJS} -I includes -o ${NAME}

clean:
	rm -f ${OBJS}

fclean:
	rm -f ${OBJS} ${NAME}

re:	fclean all

%.o: %.c ${INCL}
	${GCC} ${FLAGS} -c $< -o ${<:.c=.o}

.PHONY: all clean fclean re