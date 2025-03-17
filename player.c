/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santiago <santiago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:34:14 by mariel            #+#    #+#             */
/*   Updated: 2025/03/16 21:16:41 by santiago         ###   ########.fr       */
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

//il giocatere si ferma al limite della finestra
//si muove bene con wasd

/*void	move_player(t_player *player, t_game *game)
{
	int	speed;

	speed = 3.0f; //usando un float per avere una velocità più fluida(piu comoda pare a me)
	if (player->key_up && player->y > 0)
		player->y -= speed;
	if (player->key_down && player->y < game->screen_h - 12)
		player->y += speed;
	if (player->key_left && player->x > 0)
		player->x -= speed;
	if (player->key_right && player->x < game->screen_w - 12)
		player->x += speed;
}*/


bool is_valid_position(t_map_data *map, float x, float y)
{	
	// Converti le coordinate in pixel in coordinate in tile
    int		tile_x; 
    int		tile_y;
	char	tile;
	
	// Debug: stampa le coordinate
	printf("Checking position: (%f, %f)\n", x, y);
	
	float map_x = x - map->offset_x;
	float map_y = y - map->offset_y;
	
	tile_x = (int)(map_x / TILE_SIZE);
	tile_y = (int)(map_y / TILE_SIZE);
	
	//debug
	printf("tile: (%d, %d)\n", tile_x, tile_y);


	//debug
	printf("checking position: (%f, %f) -> Tile: (%d, %d)\n", x, y, tile_x, tile_y);
	//printf("tile content: %c\n", map->world[tile_y][tile_x]);
	
    // Controlla se la tile è valida (non è un muro e non è fuori dalla mappa)
    if (tile_x < 0 || tile_x >= map->map_width || tile_y < 0 || tile_y >= map->map_height)
	{
		printf("Error: Invalid position: out of map\n");
		return false;
	}
	
	//debug
	printf("tile content: %c\n", map->world[tile_y][tile_x]);
	
	tile = map->world[tile_y][tile_x];
	if (tile == '1')// Muro
	{
		printf("Error: position is a wall\n");
		return false;
	}
	printf("position is valid.\n");
	return true;
}

void move_player(t_player *player, t_game *game)
{
	t_map_data *map = game->map;
	float	move_speed = 3.0f; // Velocità movimento
	float	new_x;
	float	new_y;
	float	perp_dir_x;
	float	perp_dir_y;

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
	if (player->key_left)
	{
		perp_dir_x = player->dir_y;//vettore perpendicolare a sinistra
		perp_dir_y = -player->dir_x;
		new_x = player->x + perp_dir_x * move_speed;
		new_y = player->y + perp_dir_y * move_speed;
		
		if (is_valid_position(map, new_x, player->y))
			player->x = new_x;
		if (is_valid_position(map, player->x, new_y))
			player->y = new_y;
	}

	// Ruota a destra
	if (player->key_right)
	{
		perp_dir_x = -player->dir_y;
		perp_dir_y = player->dir_x;

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

/*
void	move_player(t_player *player, t_game *game)
{
	float	speed;
	float	new_x;
	float	new_y;
	
	new_x = player->x;
	new_y = player->y;
	speed = 3.0f; //usando un float per avere una velocità più fluida(piu comoda pare a me)
	printf("Before Move: (%f, %f)\n", player->x, player->y);

	if (player->key_up && player->y > 0)
		player->y -= speed;
	if (player->key_down && player->y < game->screen_h - 12)
		player->y += speed;
	if (player->key_left && player->x > 0)
		player->x -= speed;
	if (player->key_right && player->x < game->screen_w - 12)
		player->x += speed;
	new_x = player->x + (player->key_right - player->key_left) * speed;
	new_y = player->y + (player->key_down - player->key_up) * speed;	
	printf("After Move: (%f, %f)\n", player->x, player->y);

	if (is_valid_position(game->map, new_x, new_y))
	{
		player->x = new_x;
		player->y = new_y;
	}
	printf("After Move: (%f, %f)\n", player->x, player->y);

	printf("Keys: UP=%d, DOWN=%d, LEFT=%d, RIGHT=%d\n", 
		player->key_up, player->key_down, player->key_left, player->key_right);
	printf("Before Move: (%f, %f)\n", player->x, player->y);

}*/

//si muove e si blocca ma va male molto male
/*
void move_player(t_player *player, t_game *game)
{
    t_map_data *map = game->map;  // Accedi alla mappa tramite game->map
    float move_speed = 5.0f;  // Velocità del movimento
    float rot_speed = 0.03f;   // Velocità della rotazione

    if (player->key_up)  // Muovi in avanti
    {
        float new_x = player->x + player->dir_x * move_speed;
        float new_y = player->y + player->dir_y * move_speed;

        if (map->world[(int)(new_y) / TILE_SIZE][(int)(new_x) / TILE_SIZE] != '1')  // Non andare oltre i muri
        {
            player->x = new_x;
            player->y = new_y;
        }
    }
    if (player->key_down)  // Muovi indietro
    {
        float new_x = player->x - player->dir_x * move_speed;
        float new_y = player->y - player->dir_y * move_speed;

        if (map->world[(int)(new_y) / TILE_SIZE][(int)(new_x) / TILE_SIZE] != '1')
        {
            player->x = new_x;
            player->y = new_y;
        }
    }
    if (player->key_left)  // Ruota a sinistra
    {
        float old_dir_x = player->dir_x;
        player->dir_x = player->dir_x * cos(-rot_speed) - player->dir_y * sin(-rot_speed);
        player->dir_y = old_dir_x * sin(-rot_speed) + player->dir_y * cos(-rot_speed);

        float old_plane_x = player->plane_x;
        player->plane_x = player->plane_x * cos(-rot_speed) - player->plane_y * sin(-rot_speed);
        player->plane_y = old_plane_x * sin(-rot_speed) + player->plane_y * cos(-rot_speed);
    }
    if (player->key_right)  // Ruota a destra
    {
        float old_dir_x = player->dir_x;
        player->dir_x = player->dir_x * cos(rot_speed) - player->dir_y * sin(rot_speed);
        player->dir_y = old_dir_x * sin(rot_speed) + player->dir_y * cos(rot_speed);

        float old_plane_x = player->plane_x;
        player->plane_x = player->plane_x * cos(rot_speed) - player->plane_y * sin(rot_speed);
        player->plane_y = old_plane_x * sin(rot_speed) + player->plane_y * cos(rot_speed);
    }
}*/