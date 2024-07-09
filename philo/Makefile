# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 21:42:48 by yakazdao          #+#    #+#              #
#    Updated: 2024/07/04 10:14:01 by yakazdao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = philo
RM = rm -rf
FLAGS = -Wextra -Werror -Wall #-g -fsanitize=thread
MAN_SRC = 	philo.c  \
			philo_utils.c \
			functions/ft_atol.c \
			functions/ft_strlen.c \
			functions/ft_isdigit.c \
			data_init.c help_func.c \
			monitoring.c
		
MAN_OBJ = $(MAN_SRC:.c=.o)

$(NAME): $(MAN_OBJ)
	$(CC) $(FLAGS) $(MAN_OBJ) -o $(NAME)
	

all : $(NAME)

%.o : %.c philo.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(MAN_OBJ)

fclean: clean
	$(RM) $(NAME) $(MAN_OBJ)

make re: fclean all