/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:08:14 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/27 18:57:37 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_tile_color(char tile)
{
	if (tile == '1')
		return (RED);
	else if (tile == '0')
		return (BLUE);
	else if (tile == 'W' || tile == 'S' || tile == 'E' || tile == 'N')
		return (WHITE);
	return (-1);
}

void	calculate_minimap_offset(t_game *game, t_map_data *map)
{
	map->offset_minimap_x = game->screen_w
		- (map->map_width * MINIMAP_SIZE) - 120;
	map->offset_minimap_y = game->screen_h
		- (map->map_height * MINIMAP_SIZE) - 120;
}

void	draw_map_row(t_game *game, t_map_data *map, int i)
{
	int	j;

	j = 0;
	while (map->world[i][j] != '\0')
	{
		game->color_map = get_tile_color(map->world[i][j]);
		if (game->color_map != -1)
		{
			draw_square(j * MINIMAP_SIZE + map->offset_minimap_x,
				i * MINIMAP_SIZE + map->offset_minimap_y,
				MINIMAP_SIZE, game);
		}
		j++;
	}
}

void	handle_draw_map_error(t_game *game)
{
	printf("Error\nMap not loaded or empty\n");
	free_game_resources(game);
	exit(1);
}

void	draw_map(t_game *game, t_map_data *map)
{
	int	i;

	if (!map->world || !map->world[0])
		handle_draw_map_error(game);
	calculate_minimap_offset(game, map);
	i = 0;
	while (map->world[i] != NULL)
	{
		draw_map_row(game, map, i);
		i++;
	}
}
