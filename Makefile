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

NAME = cub3D
CC = clang
CFLAGS = -O3 -Wall -Wextra -Werror
MLX = ./include/mlx
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
HEADER = cub3d.h
SRC = cub3d \
		cub3d_utils \
		check_map \
		check_map_utils \
		error \
		init \
		input \
		player \
		raycast \
		raycast_utils \
		read_map \
		read_map_utils \
		render \
		texture \
		texture_utils \
		sprite \
		sprite_utils \
		save
ADD = $(addsuffix .c, $(addprefix src/, $(SRC)))
OBJ = $(ADD:.c=.o)
BIN = $(addsuffix .o, $(SRC))
EXEC = cub3D
.PHONY: all clean fclean re

all:	$(NAME)

$(NAME): $(OBJ)
	@echo "\n\033[0;33mCompiling..."
	$(MAKE) -C ./include/libft
	$(MAKE) -C ./include/gnl
	mv ./include/libft/libft.a ./include/gnl/libft_gnl.a
	ar rcs ./include/gnl/libft_gnl.a ./include/gnl/get_next_line.o
	mv ./include/gnl/libft_gnl.a ./src/
	$(CC) -L $(MLX) $(MLXFLAGS) $(OBJ) src/libft_gnl.a -I $(HEADER) -o $(EXEC)
	@echo "\033[0m"

clean:
	@echo "\033[0;31mCleaning..."
	rm -f $(OBJ) src/libft_gnl.a
	@echo "\033[0m"

fclean:	clean
	@echo "\033[0;31mRemoving executable..."
	rm -f $(NAME)
	@echo "\033[0m"
