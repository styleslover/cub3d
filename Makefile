# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 16:24:59 by mabrigo           #+#    #+#              #
#    Updated: 2025/04/27 21:10:01 by mabrigo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LIBS = -Lminilibx-linux -lmlx -lXext -lX11 -lm
GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
SRC = $(GNL) cub3d.c draw_map.c draw_player.c draw.c free_shit.c init_player.c init_texture.c init.c key_events.c map_checks_utils.c map_checks.c parsing.c player_moves.c player.c raycasting.c raycasting_utils.c utils.c parsing_fc_rgb.c parsing_fc.c parsing_map.c parsing_starter_map.c parsing_texture.c parsing_utils.c parsing_valid_path.c parsing_texture_path.c other_handle_errors.c
MINI_REPO = https://github.com/42Paris/minilibx-linux.git
MINI_PATH = minilibx-linux
MINI_ARCHIVE = $(MINI_PATH)/libmlx.a

LIBFT_PATH = libft
LIBFT_ARCHIVE = $(LIBFT_PATH)/libft.a

all: $(NAME)

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

re: fclean all

.PHONY: all clean fclean re