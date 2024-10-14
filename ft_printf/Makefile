# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/12 20:51:25 by mabrigo           #+#    #+#              #
#    Updated: 2023/11/25 12:23:51 by mabrigo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
HEADER = ft_printf.h
SOURCE = ft_putnbr_fd.c  ft_print_hex.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_printf.c ft_ptr_ptr.c ft_putunsigned_fd.c
OBJECT = $(SOURCE:.c=.o)

all: ${NAME}

${NAME}: ${OBJECT}
	ar rc ${NAME} ${OBJECT}
	ranlib ${NAME}

%.o: %.c ${HEADER}
	cc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -f ${OBJECT}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
