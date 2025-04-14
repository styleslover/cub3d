/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:34:14 by mariel            #+#    #+#             */
/*   Updated: 2025/04/14 19:28:24 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_direction(t_player *player, char c)
{
	if (c == 'W')
	{
		player->dir = PI;
		player->dir_x = -1.0f;
		player->dir_y = 0.0f;
		player->plane_x = 0.0f;
		player->plane_y = -0.66f;
	}
	else if (c == 'E')
	{
		player->dir = 0;
		player->dir_x = 1.0f;
		player->dir_y = 0.0f;
		player->plane_x = 0.0f;
		player->plane_y = 0.66f;
	}
	else if (c == 'N')
	{
		player->dir = -PI / 2;
		player->dir_x = 0.0f;
		player->dir_y = -1.0f;
		player->plane_x = 0.66f;
		player->plane_y = 0.0f;
	}
	else if (c == 'S')
	{
		player->dir = PI / 2;
		player->dir_x = 0.0f;
		player->dir_y = 1.0f;
		player->plane_x = -0.66f;
		player->plane_y = 0.0f;
	}
	return (0);
}

bool	is_valid_position(t_map_data *map, float x, float y)
{
	int		tile_x;
	int		tile_y;
	char	tile;
	int		i;
	float	map_x;
	float	map_y;

	map_x = x - map->offset_x;
	map_y = y - map->offset_y;
	tile_x = (int)(map_x / TILE_SIZE);
	tile_y = (int)(map_y / TILE_SIZE);
	i = 0;
	while (map->world[i])
	{
		printf("Map[%d]: %s\n", i, map->world[i]);
		i++;
	}
	if (tile_x < 0 || tile_x >= map->map_width
		|| tile_y < 0 || tile_y >= map->map_height)
	{
		printf("Error: Invalid position: out of map\n");
		return (false);
	}
	tile = map->world[tile_y][tile_x];
	if (tile == '1')
	{
		printf("Error: position is a wall\n");
		return (false);
	}
	return (true);
}

void	move_player(t_player *player, t_game *game)
{
	t_map_data	*map;
	float		move_speed;
	float		new_x;
	float		new_y;
	float		perp_dir_x;
	float		perp_dir_y;

	map = game->map;
	move_speed = 2.0f;
	if (player->key_up)
	{
		new_x = player->x + player->dir_x * move_speed;
		new_y = player->y + player->dir_y * move_speed;
		if (is_valid_position(map, new_x, player->y))
			player->x = new_x;
		if (is_valid_position(map, player->x, new_y))
			player->y = new_y;
	}
	if (player->key_down)
	{
		new_x = player->x - player->dir_x * move_speed;
		new_y = player->y - player->dir_y * move_speed;
		if (is_valid_position(map, new_x, player->y))
			player->x = new_x;
		if (is_valid_position(map, player->x, new_y))
			player->y = new_y;
	}
	if (player->key_left)
	{
		perp_dir_x = player->dir_y;
		perp_dir_y = -player->dir_x;
		new_x = player->x + perp_dir_x * move_speed;
		new_y = player->y + perp_dir_y * move_speed;
		if (is_valid_position(map, new_x, player->y))
			player->x = new_x;
		if (is_valid_position(map, player->x, new_y))
			player->y = new_y;
	}
	if (player->key_right)
	{
		perp_dir_x = -player->dir_y;
		perp_dir_y = player->dir_x;
		new_x = player->x + perp_dir_x * move_speed;
		new_y = player->y + perp_dir_y * move_speed;
		if (is_valid_position(map, new_x, player->y))
			player->x = new_x;
		if (is_valid_position(map, player->x, new_y))
			player->y = new_y;
	}
}
