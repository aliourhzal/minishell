# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aourhzal <aourhzal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/07 14:58:30 by ael-hadd          #+#    #+#              #
#    Updated: 2022/04/03 00:08:31 by aourhzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILE	= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
			ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c \
			ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
			ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
			ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
			ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
			ft_substr.c ft_tolower.c ft_toupper.c ft_printf.c ft_putstr.c ft_joinstr.c \
			ft_putchar.c ft_putnbr.c ft_puthex.c ft_putadd.c ft_chrjoin.c ft_strcmp.c\

NAME = libftX.a

OBJ_FILE = ft_atoi.o ft_bzero.o ft_calloc.o ft_isalnum.o ft_isalpha.o ft_isascii.o \
			ft_isdigit.o ft_isprint.o ft_itoa.o ft_memchr.o ft_memcmp.o \
			ft_memcpy.o ft_memmove.o ft_memset.o ft_putchar_fd.o ft_putendl_fd.o \
			ft_putnbr_fd.o ft_putstr_fd.o ft_split.o ft_strchr.o ft_strdup.o \
			ft_striteri.o ft_strjoin.o ft_strlcat.o ft_strlcpy.o ft_strlen.o \
			ft_strmapi.o ft_strncmp.o ft_strnstr.o ft_strrchr.o ft_strtrim.o \
			ft_substr.o ft_tolower.o ft_toupper.o ft_printf.o ft_putstr.o ft_joinstr.o \
			ft_putchar.o ft_putnbr.o ft_puthex.o ft_putadd.o ft_chrjoin.o ft_strcmp.o\


all: $(NAME)

$(NAME):	$(OBJ_FILE)
		@ar rc $(NAME) $(OBJ_FILE)

$(OBJ_FILE):	$(SRC_FILE)
		@cc -Wall -Werror -Wextra -c  $(SRC_FILE)
		

clean:
	@rm -f $(OBJ_FILE)

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)
