/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:34:14 by mariel            #+#    #+#             */
/*   Updated: 2025/02/28 18:46:11 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_player *player, t_map_data *map)
{
	int	speed;

	speed = 3.0f; //usando un float per avere una velocità più fluida(piu comoda pare a me)
	if (player->key_up && player->y > 0)
		player->y -= speed;
	if (player->key_down && player->y < map->win_height - 10)
		player->y += speed;
	if (player->key_left && player->x > 0)
		player->x -= speed;
	if (player->key_right && player->x < map->win_width - 10)
		player->x += speed;
}