# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sechang <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/01 18:29:36 by sechang           #+#    #+#              #
#    Updated: 2019/03/16 14:39:31 by sechang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
FLAGS = -Wall -Wextra -Werror
CC = gcc
OPTION = -c -I
LIB = Libft/libft.a
SRC = main.c lm_strsplit.c hashix.c phase1.c phase1b.c phase2.c phase3.c phase3b.c debug.c usage.c lm_mergesort.c sort_dist.c
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
