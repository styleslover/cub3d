/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariel <mariel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:45:26 by mariel            #+#    #+#             */
/*   Updated: 2025/02/25 00:08:15 by mariel           ###   ########.fr       */
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

void	init_player(t_player *player, t_map_data *map, int offset_x, int offset_y)
{
	int	i;
	int	j;

	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;

	i = 0;
	while(map->world[i] != NULL)
	{
		j = 0;
		while (map->world[i][j] != '\0')
		{
			if (map->world[i][j] == 'N') //giocatore posizionato nella mappa
			{
				player->x = (float)(j * TILE_SIZE + offset_x + (TILE_SIZE / 2));
				player->y = (float)(i * TILE_SIZE + offset_y + (TILE_SIZE / 2));
				player->dir = PI / 2; //guarda in alto

				//direzione iniziale
				player->dir_x = 0.0f;
				player->dir_y = -1.0f;

				//piano della camera(modifica il FOV)
				player->plane_x = 0.66f;	//0.66 valore standard per il fov
				player->plane_y = 0.0f;

				map->world[i][j] = '0';
				printf("Player initialized at (%f, %f)\n", player->x, player->y);//debug
				return ;
			}
			j++;
		}
		i++;
	}
	player->x = (float)(WIDTH / 2);
	player->y = (float)(HEIGHT / 2);
	player->dir_x = 1.0f;
	player->dir_y = 0.0f;
	player->plane_x = 0.0f;
	player->plane_y = 0.66f;
	printf("Posizione non trovata sulla mappa, posizionato al centro dello schermo\n");
}

void	init_game(t_game *game, t_map_data *map)
{
	int	screen_width;
	int	screen_height;

	game->player = malloc(sizeof(t_player));
	if (!game->player)
	{
		perror("Errore in malloc player\n");
		exit (1);
	}

	// calcolo l'offset della mappa per poterlo mandare a player
	//in modo tale da avere la posizione corretta del character
	map->map_width = (ft_strlen(map->world[0]) - 1);
	map->map_height = 0;
	while (map->world[map->map_height] != NULL)
		map->map_height++;

	map->offset_x = (WIDTH - map->map_width * TILE_SIZE) / 2;
	map->offset_y = (HEIGHT - map->map_height * TILE_SIZE) / 2;

	init_player(game->player, map, map->offset_x, map->offset_y);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		perror("errore in mlx_init\n");
		exit(1);
	}
	mlx_get_screen_size(game->mlx, &screen_width, &screen_height);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUB3D");
	if (!game->win)
	{
		perror("error in mlx_new_window\n");
		exit(1);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		perror("errore in mlx_new_image\n");
		exit(1);
	}
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	if (!game->data)
	{
		perror("errore in mlx_get_data_addr\n");
		exit (1);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	printf("Game initialized successfully\n");
}
