# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 18:46:22 by mabrigo           #+#    #+#              #
#    Updated: 2024/05/14 18:48:07 by mabrigo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT = client
SERVER = server
HEADER = minitalk.h

CC = cc
CFLAGS = -g -Wall -Wextra -Werror

LIBFT_PATH = libft
LIBFT_ARCHIVE = $(LIBFT_PATH)/libft.a

PRINTF_PATH  = printf
PRINTF_ARCHIVE = $(PRINTF_PATH)/libftprintf.a

SRC_CLIENT = client.c
SRC_SERVER = server.c

all: $(CLIENT) $(SERVER)

$(CLIENT): $(SRC_CLIENT) $(LIBFT_ARCHIVE) $(PRINTF_ARCHIVE)
	$(CC) $(CFLAGS) -o $(CLIENT) $(SRC_CLIENT) $(LIBFT_ARCHIVE) $(PRINTF_ARCHIVE)

$(SERVER): $(SRC_SERVER) $(LIBFT_ARCHIVE) $(PRINTF_ARCHIVE)
	$(CC) $(CFLAGS) -o $(SERVER) $(SRC_SERVER) $(LIBFT_ARCHIVE) $(PRINTF_ARCHIVE)

$(LIBFT_ARCHIVE):
	$(MAKE) -C $(LIBFT_PATH)

$(PRINTF_ARCHIVE):
	$(MAKE) -C $(PRINTF_PATH)

clean:
	$(MAKE) -C $(PRINTF_PATH) clean
	$(MAKE) -C $(LIBFT_PATH) clean


fclean: clean
	$(MAKE) -C $(PRINTF_PATH) fclean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(CLIENT) $(SERVER)

re: fclean all

.PHONY: all clean fclean re

.SILENT: