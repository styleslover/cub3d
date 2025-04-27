/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:23:25 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/27 18:51:57 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_memory(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	if (!game->player)
	{
		printf("Error\nError initializing player\n");
		exit(1);
	}
}

void	find_player_position(t_player *player, t_map_data *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->world[i] != NULL)
	{
		j = 0;
		while (map->world[i][j] != '\0')
		{
			if (map->world[i][j] == 'N' || map->world[i][j] == 'S'
				|| map->world[i][j] == 'E' || map->world[i][j] == 'W')
			{
				player->tile_x = j;
				player->tile_y = i;
				get_direction(player, map->world[i][j]);
				map->world[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
	handle_player_error(player, map,
		"Error\nPlayer not found in the map\n");
}

void	set_player_position(t_player *player, t_map_data *map,
		int offset_x, int offset_y)
{
	player->x = (float)(player->tile_x * TILE_SIZE + TILE_SIZE / 2) + offset_x;
	player->y = (float)(player->tile_y * TILE_SIZE + TILE_SIZE / 2) + offset_y;
	if (!is_valid_position(map, player->x, player->y))
	{
		handle_player_error(player, map, "Error\nInvalid player position\n");
	}
}

void	init_player(t_player *player, t_map_data *map,
				int offset_x, int offset_y)
{
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->rx = 0;
	player->ry = 0;
	find_player_position(player, map);
	set_player_position(player, map, offset_x, offset_y);
}

void	init_game_pointers(t_game *game)
{
	int	i;

	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->data = NULL;
	game->player = NULL;
	game->ps = NULL;
	game->map = NULL;
	i = 0;
	while (i < 4)
	{
		game->textures[i].img = NULL;
		i++;
	}
}
