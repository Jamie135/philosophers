# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 14:21:26 by pbureera          #+#    #+#              #
#    Updated: 2023/02/24 15:09:36 by pbureera         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = ./philo.c \
		./routine.c \
		./routine_norm.c \
		./init.c \
		./start_simulation.c \
		./time_functions.c \
		./print.c \
		./forks.c \
		./end_simulation.c \
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