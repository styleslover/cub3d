/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:30:39 by mariel            #+#    #+#             */
/*   Updated: 2025/03/20 20:28:09 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Permette di colorare un singolo pixel nell'immagine.
// Calcola indice del pixel nell'array data
// Controllo per evitare di uscire dallo schermo
// Impostazione del colore (blu, verde e rosso)
void	my_pixel_put(int x, int y, t_game *game, int color)
{
	int	index;

	index = y * game->size_line + x * game->bpp / 8;
	if (x >= game->screen_w || y >= game->screen_h || x < 0 || y < 0)
		return ;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	draw_direction_line(t_game *game, t_player *player, int length, int color)
{
	float	end_x;
	float	end_y;
	float	step_x;
	float	step_y;
	float	delta_x;
	float	delta_y;
	int		max_steps;
	int		i;
	float	temp_x;
	float	temp_y;

	//calcola la fine della linea in base alla direzione del giocatore
	end_x = player->x + player->dir_x * length;	//il cosf e' per i float
	end_y = player->y + player->dir_y * length;	//il sinf e' per i float
	//calcola la fine della linea in base alla direzione del giocatore
	delta_x = end_x - player->x;
	delta_y = end_y - player->y;
	max_steps = (int)fmaxf(fabsf(delta_x), fabsf(delta_y));	//fabsf per float(sarebbe abs)
	step_x = delta_x / max_steps;	//passo per x
	step_y = delta_y / max_steps;	//passo per y
	
	temp_x = player->x;
	temp_y = player->y;
	
	//disegna la linea
	i = 0;
	while (i <= max_steps)
	{
		my_pixel_put((int)temp_x, (int)temp_y, game, color);	//si arrotonda a int
		temp_x += step_x;
		temp_y += step_y;
		i++;
	}
}

void	draw_player(t_game *game, t_player *player, int size, int color)
{
	int		i;
	int		j;
	float	half_size;
	int		center_x;
	int		center_y;
	float	x;
	float	y;

	// Debug: stampa la posizione del giocatore
   //printf("Player position during drawing: (%f, %f)\n", player->x, player->y);
	
	// Calcola il centro del quadrato (personaggio)
	center_x = (int)player->x;
	center_y = (int)player->y;
	half_size = size / 2.0f;

	/*
	center_x = (int)(player->tile_x * TILE_SIZE + TILE_SIZE / 2) + game->map->offset_x;
    center_y = (int)(player->tile_y * TILE_SIZE + TILE_SIZE / 2) + game->map->offset_y;
    half_size = size / 2.0f;*/
	
	
	// Disegna il quadrato ruotato (personaggio)
	i = -half_size;
	while (i <= half_size)
	{
		j = -half_size;
		while (j <= half_size)
		{
			//calcola coordinate ruotate yeeeeeah
			x = center_x + j;
			y = center_y + i;
			rotate_point(&x, &y, center_x, center_y, player->dir);
			//disegna il pixel ruotato
			my_pixel_put((int)x, (int)y, game, color);
			j++;
		}
		i++;
	}
	//disegna la linea di direzione
	draw_direction_line(game, player, size * 4, GREEN);	//linea verde

	// draw_square(center_x - size / 2, center_y - size / 2, size, game, color);

	// // Disegna la linea di direzione
	// draw_direction_line(game, player, size * 2, GREEN); // Linea verde
}

void	draw_grid(t_game *game, t_map_data *map, int tile_size)
{
	int	x;
	int	y;

	if (!map)
		print_error("Errore draw_grid");
	// Linee orizzontali
	y = map->offset_y;
	while (y <= map->offset_y + map->map_height * tile_size)
	{
		x = map->offset_x;
		while (x <= map->offset_x + map->map_width * tile_size)
		{
			my_pixel_put(x, y, game, 0xFFFFFF);  // Linea orizzontale bianca
			x++;
		}
		y += tile_size;
	}

	// Linee verticali
	x = map->offset_x;
	while (x <= map->offset_x + map->map_width * tile_size)
	{
		y = map->offset_y;
		while (y <= map->offset_y + map->map_height * tile_size)
		{
			my_pixel_put(x, y, game, 0xFFFFFF);  // Linea verticale bianca
			y++;
		}
		x += tile_size;
	}
}

void	draw_square(int x, int y, int size, t_game *game, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_pixel_put(x + j, y + i, game, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *game, t_map_data *map)
{
	int			color;
	int			i;
	int			j;

	//printf("PORCODIO\n");
	if (!map->world || !map->world[0])
	{
		printf("Error: Map not loaded or empty\n");
		return ;
	}
	map->map_width = (ft_strlen(map->world[0]));
	map->map_height = 0;
	while (map->world[map->map_height] != NULL)
		map->map_height++;

	map->offset_x = (game->screen_w - (map->map_width * TILE_SIZE)) / 2;
	map->offset_y = (game->screen_h - (map->map_height * TILE_SIZE)) / 2;
	i = 0;
	while (map->world[i] != NULL)
	{
		j = 0;
		while (map->world[i][j] != '\0')
		{
			if (map->world[i][j] == '1')
				color = RED;
			else if (map->world[i][j] == '0')
				color = BLUE;
			else if (map->world[i][j] == 'W' || map->world[i][j] == 'S'
					|| map->world[i][j] == 'E' || map->world[i][j] == 'N')	// IGNORA 'N' O GESTISCI IL GIOCATORE	
				color = WHITE; //debugging reasons, da cambiare con BLUE
			//per qualche motivo N non me lo trova
			else
			{
				j++;
				continue;
			}
				draw_square(j * TILE_SIZE + map->offset_x,
				i * TILE_SIZE + map->offset_y, TILE_SIZE, game, color);
			j++;
		}
		i++;
	}
	//printf("Fuori while\n");
	//AGGIUNGE LA GRIGLIA DI DEBUG
	draw_grid(game, map, TILE_SIZE);
	//printf("Map drawn successfully\n");//debug
}


int	draw_loop(t_game *game)
{
	//debug
	//printf("Player position at start of draw_loop: (%f, %f)\n", game->player->x, game->player->y);
	
    move_player(game->player, game);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
    game->img = mlx_new_image(game->mlx, game->screen_w, game->screen_h);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	if (!game->map)
		print_error("Errore caricamento mappa");
	//raycasting(game);
	draw_map(game, game->map);
	draw_player(game, game->player, 12, GREEN);
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}