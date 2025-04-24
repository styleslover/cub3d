/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:34:14 by mariel            #+#    #+#             */
/*   Updated: 2025/04/24 19:37:31 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_east_west_direction(t_player *player, char c)
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
}

void	set_north_south_direction(t_player *player, char c)
{
	if (c == 'N')
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
}

void	get_direction(t_player *player, char c)
{
	if (c == 'W' || c == 'E')
		return (set_east_west_direction(player, c));
	else if (c == 'N' || c == 'S')
		return (set_north_south_direction(player, c));
}

bool	is_valid_position(t_map_data *map, float x, float y)
{
	int		tile_x;
	int		tile_y;
	float	map_x;
	float	map_y;

	map_x = x - map->offset_x;
	map_y = y - map->offset_y;
	tile_x = (int)(map_x / TILE_SIZE);
	tile_y = (int)(map_y / TILE_SIZE);
	if (tile_x < 0 || tile_x >= map->map_width
		|| tile_y < 0 || tile_y >= map->map_height)
		return (printf("Error: Invalid position: out of map\n"), false);
	if (map->world[tile_y][tile_x] == '1')
	{
		printf("Error: position is a wall\n");
		return (false);
	}
	return (true);
}

void	move_player(t_player *player, t_game *game)
{
	if (player->key_up)
		move_forward(player, game->map);
	if (player->key_down)
		move_backward(player, game->map);
	if (player->key_left)
		move_left(player, game->map);
	if (player->key_right)
		move_right(player, game->map);
}
