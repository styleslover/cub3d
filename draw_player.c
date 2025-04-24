/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:09:32 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/24 21:17:18 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(int x, int y, int size, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_pixel_put(x + j, y + i, game, game->color_map);
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *game, t_player *player, int size)
{
	int		i;
	int		j;
	float	half_size;
	int		center_x;
	int		center_y;

	center_x = (player->x - game->map->offset_x)
		* MINIMAP_SIZE / TILE_SIZE + game->map->offset_minimap_x;
	center_y = (player->y - game->map->offset_y)
		* MINIMAP_SIZE / TILE_SIZE + game->map->offset_minimap_y;
	half_size = size / 2.0f;
	i = -half_size;
	while (i <= half_size)
	{
		j = -half_size;
		while (j <= half_size)
		{
			player->rx = center_x + j;
			player->ry = center_y + i;
			rotate_point(player, center_x, center_y, player->dir);
			my_pixel_put((int)player->rx, (int)player->ry, game, game->color_player);
			j++;
		}
		i++;
	}
}
