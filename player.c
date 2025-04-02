
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:34:14 by mariel            #+#    #+#             */
/*   Updated: 2025/03/18 18:42:20 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_direction(t_player *player, char c)
{
	if (c == 'W')
	{
		player->dir = PI; // Ovest
		player->dir_x = -1.0f;
		player->dir_y = 0.0f;
	}
	else if (c == 'E')
	{
		player->dir = 0; // Est
		player->dir_x = 1.0f;
		player->dir_y = 0.0f;
	}
	else if (c == 'N')
	{
		player->dir = -PI / 2; // Nord
		player->dir_x = 0.0f;
		player->dir_y = -1.0f;
	}
	else if (c == 'S')
	{
		player->dir = PI / 2; // Sud
		player->dir_x = 0.0f;
		player->dir_y = 1.0f;
	}

	// Debug: stampa la direzione del giocatore
    printf("Player direction set to: (%f, %f)\n", player->dir_x, player->dir_y);
	
	return (0); // Default, anche se non dovrebbe mai accadere
}

bool is_valid_position(t_map_data *map, float x, float y)
{	
	// Converti le coordinate in pixel in coordinate in tile
    int		tile_x; 
    int		tile_y;
	char	tile;
	
	// Debug: stampa le coordinate
	//printf("Checking position: (%f, %f)\n", x, y);
	
	float map_x = x - map->offset_x;
	float map_y = y - map->offset_y;
	
	tile_x = (int)(map_x / TILE_SIZE);
	tile_y = (int)(map_y / TILE_SIZE);
	
	//debug
	//printf("tile: (%d, %d)\n", tile_x, tile_y);


	//debug
	//printf("checking position: (%f, %f) -> Tile: (%d, %d)\n", x, y, tile_x, tile_y);
	//printf("tile content: %c\n", map->world[tile_y][tile_x]);
	
    // Controlla se la tile è valida (non è un muro e non è fuori dalla mappa)
    if (tile_x < 0 || tile_x >= map->map_width || tile_y < 0 || tile_y >= map->map_height)
	{
		printf("Error: Invalid position: out of map\n");
		return false;
	}
	
	//debug
	//printf("tile content: %c\n", map->world[tile_y][tile_x]);
	
	tile = map->world[tile_y][tile_x];
	if (tile == '1')// Muro
	{
		printf("Error: position is a wall\n");
		return false;
	}
	//printf("position is valid.\n");
	return true;
}


void move_player(t_player *player, t_game *game)
{
	t_map_data *map = game->map;
	float	move_speed = 2.0f; // Velocità movimento
	float	new_x;
	float	new_y;
	//float	old_dir_x;
	//float	old_plane_x;

	//debug
	//printf("Player position: (%f, %f)\n", player->x, player->y);
	
	// avanti
	if (player->key_up)
	{
		new_x = player->x + player->dir_x * move_speed;//coordinate + componente del vettore direzione * velocità movi giocatore
		new_y = player->y + player->dir_y * move_speed;//new_x e new_y sono le nuove coordinate in base a direz e velocità
		//se valida(no muro) aggiorniamo coordinate
		//controllo collisioni lungo l'asse x (per le diagonali)
		//Il giocatore può muoversi lungo un asse anche se l'altro è bloccato da un muro.
		//in teoria il personaggio non scivola ma si ferma completamente al muro
		if (is_valid_position(map, new_x, player->y))
			player->x = new_x;
		//controllo collisioni lungo l'asse y	
		if (is_valid_position(map, player->x, new_y))
			player->y = new_y;
		//debug
		//printf("new player position after moving forward: (%f, %f)\n", player->x, player->y);
	}

	// indietro
	if (player->key_down)
	{
		new_x = player->x - player->dir_x * move_speed;
		new_y = player->y - player->dir_y * move_speed;
		//controllo collisioni lungo l'asse x
		if (is_valid_position(map, new_x, player->y))
			player->x = new_x;
		//controllo collisioni lungo l'asse y
		if (is_valid_position(map, player->x, new_y))
			player->y = new_y;
		//debug
		//printf("new player position after moving forward: (%f, %f)\n", player->x, player->y);
	}

	// Ruota a sinistra
	//cos(-0.03f) e sin(-0.03f) sono le funzioni trigonom. per ruotare il vettore direzione
	//e il piano della camera
	if (player->key_left)  // Ruota a sinistra (A)
	{
		float perp_dir_x = player->dir_y;
		float perp_dir_y = -player->dir_x;

		new_x = player->x + perp_dir_x * move_speed;
		new_y = player->y + perp_dir_y * move_speed;

		if (is_valid_position(map, new_x, player->y))
			player->x = new_x;
		if (is_valid_position(map, player->x, new_y))
			player->y = new_y;
	}

	if (player->key_right)  // Ruota a destra
	{
		float perp_dir_x = -player->dir_y;
		float perp_dir_y = player->dir_x;
		
		new_x = player->x + perp_dir_x * move_speed;
		new_y = player->y + perp_dir_y * move_speed;

		if (is_valid_position(map, new_x, player->y))
			player->x = new_x;
		if (is_valid_position(map, player->x, new_y))
			player->y = new_y;
	}
	/*
	if (!is_valid_position(map, new_x, new_y))
	printf("Collision detected at (%f, %f)\n", new_x, new_y);
	*/
}
