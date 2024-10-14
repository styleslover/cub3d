# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 18:33:55 by mabrigo           #+#    #+#              #
#    Updated: 2024/05/30 19:21:36 by mabrigo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADER = libft.h
SOURCES = ft_strncmp.c ft_putstr_fd.c atodbl.c
OBJECTS = ${SOURCES:.c=.o}

all: ${NAME}

#${TARGET libreria}: ${FILE da prendere}
${NAME}: ${OBJECTS}
	ar rc ${NAME} ${OBJECTS}
	ranlib ${NAME}

%.o: %.c ${HEADER}
	cc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -f ${OBJECTS}

fclean: clean
	rm -f ${NAME}
#riporta progetto a stato iniziale, non compilato

re: fclean all
#crea un nuovo eseguibile senza rimuovere file generati prima

.PHONY: all clean fclean re bonus