# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yhakamaya <yhakamaya@student.42tokyo>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/20 18:09:10 by yhakamaya         #+#    #+#              #
#    Updated: 2021/03/12 15:22:34 by matsuki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = clang
CFLAGS = -O3 -Wall -Wextra -Werror
MLX = ./include/mlx
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
HEADER = cub3d.h
SRC = cub3d \
		cub3d_utils \
		check_map \
		error \
		init \
		input \
		raycast \
		raycast_utils \
		read_map \
		read_map_utils \
		render \
		texture
ADD = $(addsuffix .c, $(addprefix src/, $(SRC)))
OBJ = $(ADD: .c=.o)
BIN = $(addsuffix .o, $(SRC))
.PHONY: all clean fclean re

all:	$(NAME)

$(NAME): $(OBJ)
	@echo "\n\033[0;33mCompiling..."
	$(MAKE) -C ./include/libft
	$(CC) $(CFLAGS) -c ./include/gnl/get_next_line.c -o ./include/gnl/get_next_line.o
	mv ./include/libft/libft.a ./include/gnl/libft_gnl.a
	ar rcs ./include/gnl/libft_gnl.a ./include/gnl/get_next_line.o
	mv ./include/gnl/libft_gnl.a ./src/
	$(CC) -L $(MLX) $(MLXFLAGS) $(OBJ) src/libft_gnl.a -I $(HEADER)
	@echo "\033[0m"

run:
	./a.out test/test.cub;

#clean:
#	@echo "\033[0;31mCleaning..."
#	rm -rf $(OBJ)
#	rm -f bitmap.bmp
#	@echo "\033[0m"

#fclean:	clean
#	@echo "\033[0;31mRemoving executable..."
#	rm -f $(NAME)
#	@echo "\033[0m"
