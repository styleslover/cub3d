/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:03:51 by damoncad          #+#    #+#             */
/*   Updated: 2025/04/27 20:01:49 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_matrix(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
}

void	free_map_textures(t_map_data *map)
{
	if (map->north_txtr)
	{
		free(map->north_txtr);
		map->north_txtr = NULL;
	}
	if (map->south_txtr)
	{
		free(map->south_txtr);
		map->south_txtr = NULL;
	}
	if (map->west_txtr)
	{
		free(map->west_txtr);
		map->west_txtr = NULL;
	}
	if (map->east_txtr)
	{
		free(map->east_txtr);
		map->east_txtr = NULL;
	}
}

void	free_map(t_map_data *map)
{
	if (!map)
		return ;
	if (map->world)
	{
		free_matrix(map->world);
		map->world = NULL;
	}
	free_map_textures(map);
	if (map->floor_color)
	{
		free(map->floor_color);
		map->floor_color = NULL;
	}
	if (map->ceiling_color)
	{
		free(map->ceiling_color);
		map->ceiling_color = NULL;
	}
}

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	if (!game || !game->mlx)
		return ;
	while (i < 4)
	{
		if (game->textures[i].img)
		{
			mlx_destroy_image(game->mlx, game->textures[i].img);
			game->textures[i].img = NULL;
		}
		i++;
	}
}

void	free_game_resources_help(t_game *game)
{
	if (game->map)
	{
		free_map(game->map);
		game->map = NULL;
	}
	if (game->player)
	{
		free(game->player);
		game->player = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	if (game->ps)
	{
		free(game->ps);
		game->ps = NULL;
	}
}
