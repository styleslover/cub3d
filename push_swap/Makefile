# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/01 22:16:44 by mabrigo           #+#    #+#              #
#    Updated: 2024/09/01 22:16:47 by mabrigo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
DEBUG_FLAGS = -g

SRCS = int_helper.c handle_errors.c init_a_to_b.c init_b_to_a.c push_swap.c push.c reverse_rotate.c rotate.c sort_stacks.c sort_utils.c sort_three.c split.c stack_init.c stack_utils.c swap.c
OBJ = $(SRCS:.c=.o)

LIBFT = ./libft/libft.a
LIBFT_PATH = ./libft

NAME = push_swap

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(PRINTF):
	make -C $(PRINTF_PATH)

$(NAME): $(OBJ) $(LIBFT) 
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re