# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sechang <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/01 18:29:36 by sechang           #+#    #+#              #
#    Updated: 2018/11/11 11:41:18 by sechang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
FLAGS = -Wall -Wextra -Werror
CC = gcc
OPTION = -c -I
LIB = Libft/libft.a
SRC = main.c lm_strsplit.c hashix.c 
OBJ = $(SRC:.c=.o) 

all: $(NAME)

$(NAME):
	make -C Libft/
#	$(CC) $(FLAGS) -o $(NAME) $(SRC) $(LIB) 
	$(CC) -o $(NAME) $(SRC) $(LIB) 
clean:
	make -C Libft/	clean
	/bin/rm -f $(OBJ)

fclean: clean
	make -C Libft/	fclean
	/bin/rm -f $(NAME)

re: fclean all
