/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_playes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:23:25 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/24 19:26:17 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_memory(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	if (!game->player)
	{
		perror("Errore in malloc player\n");
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
}

void	set_player_position(t_player *player, t_map_data *map,
		int offset_x, int offset_y)
{
	player->x = (float)(player->tile_x * TILE_SIZE + TILE_SIZE / 2) + offset_x;
	player->y = (float)(player->tile_y * TILE_SIZE + TILE_SIZE / 2) + offset_y;
	if (!is_valid_position(map, player->x, player->y))
	{
		printf("Error: invalid spawn position at (%d, %d)\n",
			player->tile_x, player->tile_y);
		exit(1);
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