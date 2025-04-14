/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:27:56 by mariel            #+#    #+#             */
/*   Updated: 2025/04/14 18:48:21 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_press_help(int keycode, t_player *player)
{
	float	old_dir_x;
	float	old_plane_x;

	if (keycode == LEFT)
	{
		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(RS) + player->dir_y * sin(RS);
		player->dir_y = -old_dir_x * sin(RS) + player->dir_y * cos(RS);
		old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(RS) + player->plane_y * sin(RS);
		player->plane_y = -old_plane_x * sin(RS) + player->plane_y * cos(RS);
	}
	if (keycode == RIGHT)
	{
		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(-RS) + player->dir_y * sin(-RS);
		player->dir_y = -old_dir_x * sin(-RS) + player->dir_y * cos(-RS);
		old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(-RS)
			+ player->plane_y * sin(-RS);
		player->plane_y = -old_plane_x * sin(-RS) + player->plane_y * cos(-RS);
	}
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
	key_press_help(keycode, player);
	if (keycode == ESC)
	{
		free_game_resources(game);
		printf("fine programma;)\n");
		exit(0);
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

int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game)
	{
		free_game_resources(game);
	}
	printf("fine programma;)\n");
	exit (0);
	return (0);
}
