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

all:
	$(MAKE) -C ./include/libft
	cp ./include/libft/libft.a ./include/gnl/libft_gnl.a
	gcc -Wall -Wextra -Werror -c ./include/gnl/get_next_line.c -o ./include/gnl/get_next_line.o
	ar rcs ./include/gnl/libft_gnl.a ./include/gnl/get_next_line.o
	mv ./include/gnl/libft_gnl.a ./src/
	gcc -L./include/mlx -lmlx -framework OpenGL -framework AppKit src/*.c src/libft_gnl.a -I include

run:
	./a.out test/test.cub;

clean:
	rm a.out;
