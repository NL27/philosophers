# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/18 18:53:37 by nlenoch           #+#    #+#              #
#    Updated: 2022/02/07 22:03:06 by nlenoch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc -pthread #-fsanitize=thread

NAME = philo

CFLAGS = -Wall -Wextra -Werror

SRC = helper.c philo.c print.c routine.c threads.c reaper.c time.c

OBJ = $(SRC:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(SRC:.c=.o)
	$(CC) -c $(SRC)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all