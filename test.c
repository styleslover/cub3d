/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:36:54 by mabrigo           #+#    #+#             */
/*   Updated: 2025/02/17 19:23:51 by mabrigo          ###   ########.fr       */
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
	if (keycode == LEFT)
		player->left_rot = true;
	if (keycode == RIGHT)
		player->right_rot = true;
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
	if (keycode == LEFT)
		player->left_rot = false;
	if (keycode == RIGHT)
		player->right_rot = false;
	return (0);
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
