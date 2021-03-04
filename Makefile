# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yhakamaya <yhakamaya@student.42tokyo>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/20 18:09:10 by yhakamaya         #+#    #+#              #
#    Updated: 2021/02/20 18:09:12 by yhakamaya        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	gcc -L./include/mlx -lmlx -framework OpenGL -framework AppKit src/*.c -I include

run:
	./a.out;

clean:
	rm a.out;
