# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-hasn <sel-hasn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/04 13:09:07 by sel-hasn          #+#    #+#              #
#    Updated: 2024/05/30 12:21:23 by sel-hasn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc 
SRC = philo.c utils.c utils1.c utils2.c utils3.c
OBJ = $(SRC:.c=.o)
RM = rm -f
FLAGS = -Wall -Wextra -Werror #-g -fsanitize=thread

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

%.o: %.c philo.h
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all