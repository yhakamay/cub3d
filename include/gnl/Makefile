# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/21 14:16:50 by yhakamay          #+#    #+#              #
#    Updated: 2021/03/21 14:16:51 by yhakamay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.o
CC = gcc
CFLAGS = -O3 -Wall -Wextra -Werror
SRCDIR = ./
SRC = $(addprefix $(SRCDIR), get_next_line.c)
OBJ = get_next_line.o
.PHONY: all clean fclean re

all:	$(NAME)
$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)
