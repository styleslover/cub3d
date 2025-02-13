# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 16:24:59 by mabrigo           #+#    #+#              #
#    Updated: 2025/02/12 16:25:00 by mabrigo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LIBS = -Lminilibx-linux -lmlx -lXext -lX11
GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
SRC = test.c $(GNL)

MINI_REPO = https://github.com/42Paris/minilibx-linux.git
MINI_PATH = minilibx-linux
MINI_ARCHIVE = $(MINI_PATH)/libmlx.a

LIBFT_PATH = libft
LIBFT_ARCHIVE = $(LIBFT_PATH)/libft.a

$(NAME): $(SRC) $(LIBFT_ARCHIVE) $(MINI_ARCHIVE)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(LIBFT_ARCHIVE) $(MINI_ARCHIVE) $(LIBS)

$(MINI_ARCHIVE): $(MINI_PATH)
	$(MAKE) -C $(MINI_PATH)

$(MINI_PATH):
	git clone $(MINI_REPO)

$(LIBFT_ARCHIVE):
	$(MAKE) -C $(LIBFT_PATH)

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	rm -rf $(MINI_PATH)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean $(NAME)

.PHONY: all clean fclean re