NAME = fractol
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LIBS = -Lminilibx-linux -lmlx -lXext -lX11
SRC = main.c utils.c render.c math_utils.c events.c

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
