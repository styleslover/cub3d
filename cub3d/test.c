/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:36:54 by mabrigo           #+#    #+#             */
/*   Updated: 2025/02/12 21:47:48 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Permette di colorare un singolo pixel nell'immagine.
// Calcola indice del pixel nell'array data
// Controllo per evitare di uscire dallo schermo
// Impostazione del colore (blu, verde e rosso)
void	my_pixel_put(int x, int y, t_game *game, int color)
{
	int	index;

	index = y * game->size_line + x * game->bpp / 8;
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

int	key_press(int keycode, t_game *game)
{
	t_player	*player;

	player = game->player;
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == ESC)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit (0);
	}
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	t_player	*player;

	player = game->player;
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	return (0);
}

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
}
void	init_game(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	if (!game->player)
	{
		perror("Errore in malloc player\n");
		exit (1);
	}
	init_player(game->player);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUB3D");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	draw_player(t_game *game, t_player *player, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_pixel_put(player->x + j, player->y + i, game, color);
			j++;
		}
		i++;
	}
}


void	move_player(t_player *player)
{
	int	speed;

	speed = 1;
	if (player->key_up && player->y > 0)
		player->y -= speed;
	if (player->key_down && player->y < HEIGHT - 10)
		player->y += speed;
	if (player->key_left && player->x > 0)
		player->x -= speed;
	if (player->key_right && player->x < WIDTH - 10)
		player->x += speed;
}

int	draw_loop(t_game *game)
{
	t_player *player;

	player = game->player;
	move_player(player);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	draw_player(game, player, 10, 0xFF00FF);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	main ()
{
	t_game		game;

	init_game(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	free(game.player);
	return (0);
}
