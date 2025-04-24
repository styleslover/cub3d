/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:35:22 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/24 19:37:43 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_player *player, t_map_data *map)
{
	float	new_x;
	float	new_y;
	float	move_speed;

	move_speed = 2.0f;
	new_x = player->x + player->dir_x * move_speed;
	new_y = player->y + player->dir_y * move_speed;
	if (is_valid_position(map, new_x, player->y))
		player->x = new_x;
	if (is_valid_position(map, player->x, new_y))
		player->y = new_y;
}

void	move_backward(t_player *player, t_map_data *map)
{
	float	new_x;
	float	new_y;
	float	move_speed;

	move_speed = 2.0f;
	new_x = player->x - player->dir_x * move_speed;
	new_y = player->y - player->dir_y * move_speed;
	if (is_valid_position(map, new_x, player->y))
		player->x = new_x;
	if (is_valid_position(map, player->x, new_y))
		player->y = new_y;
}

void	move_left(t_player *player, t_map_data *map)
{
	float	new_x;
	float	new_y;
	float	perp_dir_x;
	float	perp_dir_y;
	float	move_speed;

	move_speed = 2.0f;
	perp_dir_x = player->dir_y;
	perp_dir_y = -player->dir_x;
	new_x = player->x + perp_dir_x * move_speed;
	new_y = player->y + perp_dir_y * move_speed;
	if (is_valid_position(map, new_x, player->y))
		player->x = new_x;
	if (is_valid_position(map, player->x, new_y))
		player->y = new_y;
}

void	move_right(t_player *player, t_map_data *map)
{
	float	new_x;
	float	new_y;
	float	perp_dir_x;
	float	perp_dir_y;
	float	move_speed;

	move_speed = 2.0f;
	perp_dir_x = -player->dir_y;
	perp_dir_y = player->dir_x;
	new_x = player->x + perp_dir_x * move_speed;
	new_y = player->y + perp_dir_y * move_speed;
	if (is_valid_position(map, new_x, player->y))
		player->x = new_x;
	if (is_valid_position(map, player->x, new_y))
		player->y = new_y;
}

void	rotate_point(t_player *player, float center_x,
	float center_y, float angle)
{
	float	sin_angle;
	float	cos_angle;
	float	translated_x;
	float	translated_y;

	translated_x = player->rx - center_x;
	translated_y = player->ry - center_y;
	sin_angle = sinf(angle);
	cos_angle = cosf(angle);
	player->rx = translated_x * cos_angle - translated_y * sin_angle + center_x;
	player->ry = translated_x * sin_angle + translated_y * cos_angle + center_y;
}