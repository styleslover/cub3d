/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:34:14 by mariel            #+#    #+#             */
/*   Updated: 2025/03/10 11:10:28 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_direction(t_player *player, char c)
{
	if (c == 'W')
	{
		player->dir = PI; // Ovest
		player->dir_x = -1.0f;
		player->dir_y = 0.0f;
	}
	else if (c == 'E')
	{
		player->dir = 0; // Est
		player->dir_x = 1.0f;
		player->dir_y = 0.0f;
	}
	else if (c == 'N')
	{
		player->dir = -PI / 2; // Nord
		player->dir_x = 0.0f;
		player->dir_y = -1.0f;
	}
	else if (c == 'S')
	{
		player->dir = PI / 2; // Sud
		player->dir_x = 0.0f;
		player->dir_y = 1.0f;
	}

	// if (c == 'N')
	// 	return (3 * PI / 2); // 270° (su)
	// else if (c == 'S')
	// 	return (PI / 2); // 90° (giù)
	// else if (c == 'E')
	// 	return (0); // 0° (destra)
	// else if (c == 'W')
	// 	return (PI); // 180° (sinistra)
	return (0); // Default, anche se non dovrebbe mai accadere
}

//il giocatere si ferma al limite della finestra ma in basso e' coperta dalla barra predefinita di linux
void	move_player(t_player *player, t_game *game)
{
	int	speed;

	speed = 3.0f; //usando un float per avere una velocità più fluida(piu comoda pare a me)
	if (player->key_up && player->y > 0)
		player->y -= speed;
	if (player->key_down && player->y < game->screen_h - 15)
		player->y += speed;
	if (player->key_left && player->x > 0)
		player->x -= speed;
	if (player->key_right && player->x < game->screen_w - 15)
		player->x += speed;
}