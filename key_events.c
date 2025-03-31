/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:27:56 by mariel            #+#    #+#             */
/*   Updated: 2025/03/24 18:35:00 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int key_press(int keycode, t_game *game)
{
    t_player *player;
	
	player = game->player;

    if (keycode == W)
        player->key_up = true;
    if (keycode == S)
        player->key_down = true;
    if (keycode == A)
        player->key_left = true;
    if (keycode == D)
        player->key_right = true;

    // Rotazione con frecce
    if (keycode == LEFT)  // Ruota a sinistra
    {
        float old_dir_x = player->dir_x;
        player->dir_x = player->dir_x * cos(ROTASPEED) + player->dir_y * sin(ROTASPEED);
        player->dir_y = -old_dir_x * sin(ROTASPEED) + player->dir_y * cos(ROTASPEED);

        float old_plane_x = player->plane_x;
        
        player->plane_x = player->plane_x * cos(ROTASPEED) + player->plane_y * sin(ROTASPEED);
        player->plane_y = -old_plane_x * sin(ROTASPEED) + player->plane_y * cos(ROTASPEED);

        printf("Rotated left. New direction: (%f, %f)\n", player->dir_x, player->dir_y);  // Debug
    }

    if (keycode == RIGHT)  // Ruota a destra
    {
        float old_dir_x = player->dir_x;
        player->dir_x = player->dir_x * cos(-ROTASPEED) + player->dir_y * sin(-ROTASPEED);
        player->dir_y = -old_dir_x * sin(-ROTASPEED) + player->dir_y * cos(-ROTASPEED);

        float old_plane_x = player->plane_x;
        
        player->plane_x = player->plane_x * cos(-ROTASPEED) + player->plane_y * sin(-ROTASPEED);
        player->plane_y = -old_plane_x * sin(-ROTASPEED) + player->plane_y * cos(-ROTASPEED);

        printf("Rotated right. New direction: (%f, %f)\n", player->dir_x, player->dir_y);  // Debug
    }
    
    if (keycode == SPACE) {  // Codice per SPACE
        static int color = 0xFF0000;  // Rosso
        color = (color == 0xFF0000) ? 0x00FF00 : 0xFF0000;  // Alterna rosso/verde
        for (int x = 0; x < 100; x++) {
            for (int y = 0; y < 20; y++) {
                my_pixel_put(game->screen_w/2 - 50 + x, game->screen_h - 100 + y, game, color);
            }
        }
    }
	
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