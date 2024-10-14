# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 18:33:55 by mabrigo           #+#    #+#              #
#    Updated: 2024/05/13 19:04:21 by mabrigo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADER = libft.h
SOURCES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_strnstr.c\
			ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c \
			ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_memcmp.c\
			ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
			ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
			ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c 
OBJECTS = ${SOURCES:.c=.o}

all: ${NAME}

#${TARGET libreria}: ${FILE da prendere}
${NAME}: ${OBJECTS}
	ar rc ${NAME} ${OBJECTS}
	ranlib ${NAME}

bonus: ${BOBJECTS} ${OBJECTS}
	ar rc ${NAME} ${OBJECTS}

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