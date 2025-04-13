/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:45:26 by mariel            #+#    #+#             */
/*   Updated: 2025/04/13 19:14:54 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void load_texture(t_game *game, t_textures *texture, char *path)
{
	char *clean_path;

	clean_path = ft_strtrim(path, "\t\n\r");//da trovare soluzione migliore
    texture->img = mlx_xpm_file_to_image(game->mlx, clean_path, &texture->width, &texture->height);
	
    if (!texture->img)
    {
		printf("Error: Could not load texture.\n");
		perror("Reason");
		free_map(game->map);
        exit(1);
    }
    texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, 
		&texture->line_length, &texture->endian);
	//free(path);
	free(clean_path);
}

void init_textures(t_game *game, t_map_data *map)
{
    load_texture(game, &game->textures[0], map->north_txtr); // Nord
    load_texture(game, &game->textures[1], map->south_txtr); // Sud
    load_texture(game, &game->textures[2], map->east_txtr);  // Est
    load_texture(game, &game->textures[3], map->west_txtr);  // Ovest
}

void	init_map(t_map_data *map)
{
	map->map_height = 0;
	map->map_width = 0;
	map->win_height = 0;
	map->win_width = 0;
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
			if (map->world[i][j] == 'N' || map->world[i][j] == 'S'
				|| map->world[i][j] == 'E' || map->world[i][j] == 'W')
			{
				player->tile_x = j;
				player->tile_y = i;
				player->x = (float)(j * TILE_SIZE + TILE_SIZE / 2) + offset_x;
				player->y = (float)(i * TILE_SIZE + TILE_SIZE / 2) + offset_y;

				//verifica posizione spawn valida
				if (!is_valid_position(map, player->x, player->y))
				{
					printf("Error: invalid spawn position at (%d, %d)\n", j, i);
					exit(1);
				}
				

				get_direction(player, map->world[i][j]);

				map->world[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

void	init_game(char *name_win, t_game *game, t_map_data *map)
{
	game->map = map;
	game->player = malloc(sizeof(t_player));
	if (!game->player)
	{
		perror("Errore in malloc player\n");
		exit (1);
	}
	if (map->win_width == 0 || map->win_height == 0)
	{
		perror("Errore: Dimensioni della mappa non valide\n");
		//free_map(map); //messo riduce a 40 i still reachable
		exit(1);
	}
	// Ottieni la dimensione massima dello schermo
	game->mlx = mlx_init();
	mlx_get_screen_size(game->mlx, &game->screen_w, &game->screen_h);

	// Limita la finestra alla dimensione massima dello schermo
	if (map->win_width > game->screen_w)
		map->win_width = game->screen_w;
	else
		map->win_width = game->screen_w;
		
	if (map->win_height > game->screen_h)
		map->win_height = game->screen_h;
	else
		map->win_height = game->screen_h;
		
	// Calcola offset per centrare la mappa nella finestra
	map->offset_x = (map->win_width - (map->map_width * TILE_SIZE)) / 2;
	map->offset_y = (map->win_height - (map->map_height * TILE_SIZE)) / 2;
	if (map->offset_x < 0) map->offset_x = 0;
	if (map->offset_y < 0) map->offset_y = 0;

	game->cos_rot_speed = cos(ROTASPEED);
	game->sin_rot_speed = sin(ROTASPEED);
	
	//load_textures(game);//PER CARICARE LE TEXTURES, DA CAPIRE DOVE VA PER BENE
	init_textures(game, map);
	init_player(game->player, map, map->offset_x, map->offset_y);

	// Crea la finestra
	game->win = mlx_new_window(game->mlx, game->screen_w, game->screen_h, name_win);
	if (!game->win)
	{
		perror("Errore in mlx_new_window\n");
		exit(1);
	}

	// Crea l'immagine
	game->img = mlx_new_image(game->mlx, game->screen_w, game->screen_h);
	if (!game->img)
	{
		perror("Errore in mlx_new_image\n");
		exit(1);
	}

	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	if (!game->data)
	{
		perror("Errore in mlx_get_data_addr\n");
		exit (1);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	printf("Game initialized successfully\n");
}