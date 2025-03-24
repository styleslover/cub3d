/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:30:39 by mariel            #+#    #+#             */
/*   Updated: 2025/03/24 16:50:57 by damoncad         ###   ########.fr       */
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
//draw_player originale quello classico
// void	draw_player(t_game *game, t_player *player, int size, int color)
// {
// 	int		i;
// 	int		j;
// 	float	half_size;
// 	int		center_x;
// 	int		center_y;
// 	float	x;
// 	float	y;

// 	// Debug: stampa la posizione del giocatore
//    //printf("Player position during drawing: (%f, %f)\n", player->x, player->y);
	
// 	// Calcola il centro del quadrato (personaggio)
// 	center_x = (int)player->x;
// 	center_y = (int)player->y;
// 	half_size = size / 2.0f;

// 	/*
// 	center_x = (int)(player->tile_x * TILE_SIZE + TILE_SIZE / 2) + game->map->offset_x;
//     center_y = (int)(player->tile_y * TILE_SIZE + TILE_SIZE / 2) + game->map->offset_y;
//     half_size = size / 2.0f;*/
	
	
// 	// Disegna il quadrato ruotato (personaggio)
// 	i = -half_size;
// 	while (i <= half_size)
// 	{
// 		j = -half_size;
// 		while (j <= half_size)
// 		{
// 			//calcola coordinate ruotate yeeeeeah
// 			x = center_x + j;
// 			y = center_y + i;
// 			rotate_point(&x, &y, center_x, center_y, player->dir);
// 			//disegna il pixel ruotato
// 			my_pixel_put((int)x, (int)y, game, color);
// 			j++;
// 		}
// 		i++;
// 	}
// 	//disegna la linea di direzione
// 	draw_direction_line(game, player, size * 4, GREEN);	//linea verde

// 	// draw_square(center_x - size / 2, center_y - size / 2, size, game, color);

// 	// // Disegna la linea di direzione
// 	// draw_direction_line(game, player, size * 2, GREEN); // Linea verde
// }




//draw_grid originale
// void	draw_grid(t_game *game, t_map_data *map, int tile_size)
// {
// 	int	x;
// 	int	y;

// 	if (!map)
// 		print_error("Errore draw_grid");
// 	// Linee orizzontali
// 	y = map->offset_y;
// 	while (y <= map->offset_y + map->map_height * tile_size)
// 	{
// 		x = map->offset_x;
// 		while (x <= map->offset_x + map->map_width * tile_size)
// 		{
// 			my_pixel_put(x, y, game, 0xFFFFFF);  // Linea orizzontale bianca
// 			x++;
// 		}
// 		y += tile_size;
// 	}

// 	// Linee verticali
// 	x = map->offset_x;
// 	while (x <= map->offset_x + map->map_width * tile_size)
// 	{
// 		y = map->offset_y;
// 		while (y <= map->offset_y + map->map_height * tile_size)
// 		{
// 			my_pixel_put(x, y, game, 0xFFFFFF);  // Linea verticale bianca
// 			y++;
// 		}
// 		x += tile_size;
// 	}
// }

//draw_quare quello buono
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
//vecchio classico draw_map
// void	draw_map(t_game *game, t_map_data *map)
// {
// 	int			color;
// 	int			i;
// 	int			j;

// 	//printf("PORCODIO\n");
// 	if (!map->world || !map->world[0])
// 	{
// 		printf("Error: Map not loaded or empty\n");
// 		return ;
// 	}
// 	map->map_width = (ft_strlen(map->world[0]));
// 	map->map_height = 0;
// 	while (map->world[map->map_height] != NULL)
// 		map->map_height++;

// 	map->offset_x = (game->screen_w - (map->map_width * TILE_SIZE)) / 2;
// 	map->offset_y = (game->screen_h - (map->map_height * TILE_SIZE)) / 2;
// 	i = 0;
// 	while (map->world[i] != NULL)
// 	{
// 		j = 0;
// 		while (map->world[i][j] != '\0')
// 		{
// 			if (map->world[i][j] == '1')
// 				color = RED;
// 			else if (map->world[i][j] == '0')
// 				color = BLUE;
// 			else if (map->world[i][j] == 'W' || map->world[i][j] == 'S'
// 					|| map->world[i][j] == 'E' || map->world[i][j] == 'N')	// IGNORA 'N' O GESTISCI IL GIOCATORE	
// 				color = WHITE; //debugging reasons, da cambiare con BLUE
// 			//per qualche motivo N non me lo trova
// 			else
// 			{
// 				j++;
// 				continue;
// 			}
// 				draw_square(j * TILE_SIZE + map->offset_x,
// 				i * TILE_SIZE + map->offset_y, TILE_SIZE, game, color);
// 			j++;
// 		}
// 		i++;
// 	}
// 	//printf("Fuori while\n");
// 	//AGGIUNGE LA GRIGLIA DI DEBUG
// 	draw_grid(game, map, TILE_SIZE);
// 	//printf("Map drawn successfully\n");//debug
// }








void	draw_player(t_game *game, t_player *player, int size, int color)
{
	//t_map_data	*map = game->map;
	int		i;
	int		j;
	float	half_size;
	int		center_x;
	int		center_y;
	float	x;
	float	y;

	//Calcola il centro del quadrato (personaggio)
	center_x = (player->x - game->map->offset_x) * MINIMAP_SIZE / TILE_SIZE + game->map->offset_minimap_x;
	center_y = (player->y - game->map->offset_y) * MINIMAP_SIZE / TILE_SIZE + game->map->offset_minimap_y;
	half_size = size / 2.0f;
	

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
	//draw_direction_line(game, player, size * 4, GREEN);	//linea verde

}



//in realta, a che cazzo serve la grid nella mini mappa??, direi quasi bone
void	draw_grid(t_game *game, t_map_data *map, int tile_size)
{
	int	x;
	int	y;

	if (!map)
		print_error("Errore draw_grid");
	// Linee orizzontali
	y = map->offset_minimap_x;
	while (y <= map->offset_minimap_y + map->map_height * tile_size)
	{
		x = map->offset_minimap_x;
		while (x <= map->offset_minimap_x + map->map_width * tile_size)
		{
			my_pixel_put(x, y, game, 0xFFFFFF);  // Linea orizzontale bianca
			x++;
		}
		y += tile_size;
	}

	// Linee verticali
	x = map->offset_minimap_x;
	while (x <= map->offset_minimap_x + map->map_width * tile_size)
	{
		y = map->offset_minimap_y;
		while (y <= map->offset_minimap_y + map->map_height * tile_size)
		{
			my_pixel_put(x, y, game, 0xFFFFFF);  // Linea verticale bianca
			y++;
		}
		x += tile_size;
	}
}

void draw_minimap_border(t_game *game, t_map_data *map)
{
    // Calcola la posizione di partenza per il bordo
    int minimap_width = map->map_width * MINIMAP_SIZE;
    int minimap_height = map->map_height * MINIMAP_SIZE;

    int offset_x = map->offset_minimap_x;
    int offset_y = map->offset_minimap_y;

    // Colore del bordo
    int border_color = 0xFFFFFF;  // Bianco, ma puoi cambiarlo come vuoi

    // Disegna il bordo: 4 linee (superiore, inferiore, sinistra, destra)
    int x, y;

    // Bordo superiore
    for (x = offset_x; x < offset_x + minimap_width; x++) {
        my_pixel_put(x, offset_y, game, border_color);  // Linea orizzontale in alto
    }

    // Bordo inferiore
    for (x = offset_x; x < offset_x + minimap_width; x++) {
        my_pixel_put(x, offset_y + minimap_height - 1, game, border_color);  // Linea orizzontale in basso
    }

    // Bordo sinistro
    for (y = offset_y; y < offset_y + minimap_height; y++) {
        my_pixel_put(offset_x, y, game, border_color);  // Linea verticale a sinistra
    }

    // Bordo destro
    for (y = offset_y; y < offset_y + minimap_height; y++) {
        my_pixel_put(offset_x + minimap_width - 1, y, game, border_color);  // Linea verticale a destra
    }
}

//il draw_map per fare la minimappa ultimo buono
void	draw_map(t_game *game, t_map_data *map)
{
	int			color;
	int			i;
	int			j;

	// Controllo che la mappa sia caricata
	if (!map->world || !map->world[0])
	{
		printf("Error: Map not loaded or empty\n");
		return;
	}


	// Calcola gli offset della minimappa SENZA toccare gli offset principali della mappa
	map->offset_minimap_x = game->screen_w - (map->map_width * MINIMAP_SIZE) - 120;
	map->offset_minimap_y = game->screen_h - (map->map_height * MINIMAP_SIZE) - 120;

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
			else if (map->world[i][j] == 'W' || map->world[i][j] == 'S' ||
			         map->world[i][j] == 'E' || map->world[i][j] == 'N')
				color = WHITE; // Debugging, eventualmente da cambiare

			else
			{
				j++;
				continue;
			}

			// Disegna il tile scalato nella posizione corretta
			draw_square(j * MINIMAP_SIZE + map->offset_minimap_x,
			            i * MINIMAP_SIZE + map->offset_minimap_y,
			            MINIMAP_SIZE, game, color);
			j++;
		}
		i++;
	}

	draw_minimap_border(game, map);  // Disegna il bordo della minimappa
	// Aggiunge la griglia alla minimappa (opzionale)
	//draw_grid(game, map, 15 * TILE_SIZE);
}

void	paint_floor_ceiling(t_game *game, int floor, int ceiling)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->screen_h)
	{
		x = 0;
		while (x < game->screen_w)
		{
			if (y < game->screen_h / 2)
				my_pixel_put(x, y, game, ceiling);
			else
				my_pixel_put(x, y, game, floor);
			x++;
		}
		y++;
	}
}

void	draw_floor_ceiling(t_game *game, t_map_data *map)
{
	int	floor_color;
	int	ceiling_color;

	if (map->floor_color)
	{
		floor_color = ((map->floor_color[0] << 16)
				| (map->floor_color[1] << 8) | (map->floor_color[2]));
	}
	else
	{
		printf("Warning: Invalid floor color, using default color (black).\n");
        floor_color = 0x000000;
	}
	if (map->ceiling_color)
	{
		ceiling_color = ((map->ceiling_color[0] << 16)
				| (map->ceiling_color[1] << 8) | (map->ceiling_color[2]));
	}
	else
	{
		printf("Warning: Invalid ceiling color, using default color (white).\n");
        ceiling_color = 0xFFFFFF;
		return ;
	}
	paint_floor_ceiling(game, floor_color, ceiling_color);
}












//MINIMAPPA TONDA DA SVILUPPARE------------->
/*
void draw_line(int x0, int y0, int x1, int y1, t_game *game, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;

    while (1)
    {
        my_pixel_put(x0, y0, game, color);
        if (x0 == x1 && y0 == y1) break;
        int e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 < dy)  { err += dx; y0 += sy; }
    }
}


void draw_circle(int center_x, int center_y, int radius, t_game *game, int color)
{
    int x, y;
    for (y = -radius; y <= radius; y++)
    {
        for (x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
            {
                my_pixel_put(center_x + x, center_y + y, game, color);
            }
        }
    }
}

void draw_map(t_game *game, t_map_data *map)
{
    int color;
    int i, j;
    int minimap_radius = 60;  // Raggio della minimappa rotonda
    int center_x = game->screen_w - minimap_radius - 120;  // Posizione X del centro
    int center_y = game->screen_h - minimap_radius - 120;  // Posizione Y del centro

    // Disegna il bordo della minimappa rotonda
    draw_circle(center_x, center_y, minimap_radius, game, 0xFFFFFF);  // Bianco

    // Calcola la posizione del giocatore nella minimappa
    //float player_minimap_x = center_x;
    //float player_minimap_y = center_y;

    // Disegna la mappa ruotata attorno al giocatore
    for (i = 0; map->world[i] != NULL; i++)
    {
        for (j = 0; map->world[i][j] != '\0'; j++)
        {
            if (map->world[i][j] == '1')
                color = RED;
            else if (map->world[i][j] == '0')
                color = BLUE;
            else
                continue;

            // Calcola le coordinate relative al giocatore
            float rel_x = (j * TILE_SIZE + map->offset_x - game->player->x) * MINIMAP_SIZE / TILE_SIZE;
            float rel_y = (i * TILE_SIZE + map->offset_y - game->player->y) * MINIMAP_SIZE / TILE_SIZE;

            // Ruota le coordinate in base alla direzione del giocatore
            float rotated_x = rel_x * cosf(-game->player->dir) - rel_y * sinf(-game->player->dir);
            float rotated_y = rel_x * sinf(-game->player->dir) + rel_y * cosf(-game->player->dir);

            // Posizione nella minimappa
            int minimap_x = center_x + (int)rotated_x;
            int minimap_y = center_y + (int)rotated_y;

            // Disegna solo se è dentro il cerchio
            if ((minimap_x - center_x) * (minimap_x - center_x) + 
                (minimap_y - center_y) * (minimap_y - center_y) <= minimap_radius * minimap_radius)
            {
                my_pixel_put(minimap_x, minimap_y, game, color);
            }
        }
    }

    // Disegna il giocatore al centro della minimappa
    draw_player_minimap(game, center_x, center_y, 5, GREEN);  // 5 è la dimensione del giocatore
}


void draw_player_minimap(t_game *game, int center_x, int center_y, int size, int color)
{
    int i, j;
    float half_size = size / 2.0f;

    for (i = -half_size; i <= half_size; i++)
    {
        for (j = -half_size; j <= half_size; j++)
        {
            if (i * i + j * j <= half_size * half_size)
            {
                my_pixel_put(center_x + j, center_y + i, game, color);
            }
        }
    }

    // Disegna la linea di direzione
    //float end_x = center_x + cosf(game->player->dir) * size * 2;
    //float end_y = center_y + sinf(game->player->dir) * size * 2;
    //draw_line(center_x, center_y, (int)end_x, (int)end_y, game, color);
}
*/



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
	draw_floor_ceiling(game, game->map);
	raycasting(game);
	draw_map(game, game->map);
	draw_player(game, game->player, 8, GREEN);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}