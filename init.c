/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:45:26 by mariel            #+#    #+#             */
/*   Updated: 2025/04/24 19:31:56 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_map_data *map)
{
	map->map_height = 0;
	map->map_width = 0;
	map->east_txtr = NULL;
	map->north_txtr = NULL;
	map->south_txtr = NULL;
	map->west_txtr = NULL;
	map->ceiling_color = NULL;
	map->floor_color = NULL;
	map->world = NULL;
}

void	init_screen_and_offsets(t_game *game, t_map_data *map)
{
	game->mlx = mlx_init();
	mlx_get_screen_size(game->mlx, &game->screen_w, &game->screen_h);
	map->offset_x = ((map->map_width * TILE_SIZE)) / 2;
	map->offset_y = ((map->map_height * TILE_SIZE)) / 2;
	if (map->offset_x < 0)
		map->offset_x = 0;
	if (map->offset_y < 0)
		map->offset_y = 0;
	game->cos_rot_speed = cos(RS);
	game->sin_rot_speed = sin(RS);
}

void	init_raycasting_memory(t_game *game)
{
	game->ps = malloc(sizeof(t_raycasting_shit));
	if (!game->ps)
	{
		perror("Errore in game->ps\n");
		exit(1);
	}
	init_raycasting_shit(game->ps);
}

void	init_window_and_image(t_game *game, char *name_win)
{
	game->win = mlx_new_window(game->mlx, game->screen_w,
			game->screen_h, name_win);
	if (!game->win)
	{
		perror("Errore in mlx_new_window\n");
		exit(1);
	}
	game->img = mlx_new_image(game->mlx, game->screen_w, game->screen_h);
	if (!game->img)
	{
		perror("Errore in mlx_new_image\n");
		exit(1);
	}
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	if (!game->data)
	{
		perror("Errore in mlx_get_data_addr\n");
		exit(1);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	init_game(char *name_win, t_game *game, t_map_data *map)
{
	game->map = map;
	init_player_memory(game);
	init_screen_and_offsets(game, map);
	init_raycasting_memory(game);
	init_textures(game, map);
	init_player(game->player, map, map->offset_x, map->offset_y);
	init_window_and_image(game, name_win);
	printf("Game initialized successfully\n");
}
