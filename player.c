/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:04:03 by mabrigo           #+#    #+#             */
/*   Updated: 2025/02/12 19:04:39 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->x = HEIGHT / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
}

void	move_player(t_player *player)
{
	int	speed;

	speed = 5;
	if (player->key_up && player->y > 0)
		player->y -= speed;
	if (player->key_down && player->y < HEIGHT - 10)
		player->y += speed;
	if (player->key_left && player->x > 0)
		player->x -= speed;
	if (player->key_right && player->x < WIDTH - 10)
		player->x += speed;
}
	//  //da finire con video
	// void	turn_player(t_player *player)
	// {
	// 	float	speed;
	// 	float	cos_angle;
	// 	float	sin_angle;
	
	// 	speed = 0.1;
	// 	cos_angle = cos(player->angle);
	// 	sin_angle = sin(player->angle);
	// 	if (player->left_rot)
	// 	player->angle -= speed;
	// 	if (player->right_rot)
	// 	player->angle += speed;	
	// 	if (player->angle > 2 * PI)
	// 	player->angle = 0;
	// 	if 	(player->angle < 0)
	// 	player->angle = 2 * PI;
	// 	if (player->key_up)
	// 	{
	// 		player->x += cos_angle * speed;
	// 		player->x += sin_angle * speed;
	// 	}
	// 	if (player->key_down)
	// 	{
	// 		player->x -= cos_angle * speed;
	// 		player->x -= sin_angle * speed;
	// 	}
	// 	if (player->key_left)
	// 	{
	// 		player->x += cos_angle * speed;
	// 		player->x -= sin_angle * speed;
	// 	}
	// 	if (player->key_up)
	// 	{
	// 		player->x -= cos_angle * speed;
	// 		player->x += sin_angle * speed;
	// 	}
	// }
	
	//con else if funziona??
	// void	move_player(t_player *player)
	// {
		// 	int		speed;
		
		// 	speed = 2;
		// 	if (player->key_up && player->y > 0)
		// 		player->y -= speed;
		// 	else if (player->key_down && player->y < HEIGHT - 10)
		// 		player->y += speed;
// 	else if (player->key_left && player->x > 0)
// 		player->x -= speed;
// 	else if (player->key_right && player->x < WIDTH - 10)
// 		player->x += speed;
// 	else
// 		turn_player(player);
// }
