# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yhakamaya <yhakamaya@student.42tokyo>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/22 09:33:53 by yhakamaya         #+#    #+#              #
#    Updated: 2021/02/22 09:50:05 by yhakamaya        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
INCDIR	= ./libft
SRCDIR	= ./
# SNAME	= 
SRCS	= $(addprefix $(SRCDIR), $(NAME))
OBJS	= $(SRCS:.c=.o)

all:		$(NAME)
$(NAME):	$(OBJS)
				ar rc $(NAME) $(OBJS)
.c.o:			$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $(<:.c=.o)
clean:			rm -f $(OBJS)
fclean:		clean
				rm -f $(NAME)
re:				fclean all

.PHONY:		all bonus clean fclean re
