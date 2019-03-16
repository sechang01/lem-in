# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sechang <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/16 09:56:58 by sechang           #+#    #+#              #
#    Updated: 2019/03/04 14:52:00 by sechang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror
CC = gcc
OPTION = -c -I
SRC0 = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c \
	ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c \
	ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c \
	ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c \
	ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
	ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c \
	ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c \
	ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c \
	ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
	ft_lstmap.c \
	ft_get_intlen.c ft_isupper.c ft_islower.c ft_iswhitespace.c ft_getwords.c\
	Get_next_line/get_next_line.c \
	Printf/ft_printf.c \
	Printf/ft_fprintf.c \
	Printf/lettermatch.c \
	Printf/fmtr.c \
	Printf/charific.c \
	Printf/numeric.c \
	Printf/printf_u.c \
	Printf/printf_o.c \
	Printf/printf_x.c \
	Printf/itoabase.c \
	LinkedList/ft_stack.c \
	LinkedList/ft_queue.c 
SRCDIR = src/
SRC = $(addprefix $(SRCDIR), $(SRC0))
OBJ = *.o
all: $(NAME)

$(NAME):
	@gcc -c $(FLAGS) $(SRC) -I inc/
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[1;32m[Compiled]\033[0m: \033[1;33mLibary Compiled\033[0m"

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)
	

re: fclean all
