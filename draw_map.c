/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:08:14 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/24 19:08:24 by mabrigo          ###   ########.fr       */
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
	int	color;

	j = 0;
	while (map->world[i][j] != '\0')
	{
		color = get_tile_color(map->world[i][j]);
		if (color != -1)
		{
			draw_square(j * MINIMAP_SIZE + map->offset_minimap_x,
				i * MINIMAP_SIZE + map->offset_minimap_y,
				MINIMAP_SIZE, game, color);
		}
		j++;
	}
}

void	draw_map(t_game *game, t_map_data *map)
{
	int	i;

	if (!map->world || !map->world[0])
	{
		printf("Error: Map not loaded or empty\n");
		return ;
	}
	calculate_minimap_offset(game, map);
	i = 0;
	while (map->world[i] != NULL)
	{
		draw_map_row(game, map, i);
		i++;
	}
}