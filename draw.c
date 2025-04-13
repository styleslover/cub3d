/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:30:39 by mariel            #+#    #+#             */
/*   Updated: 2025/04/13 16:36:08 by damoncad         ###   ########.fr       */
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

	//draw_minimap_border(game, map);  // Disegna il bordo della minimappa
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
		printf("Warning: Invalid floor color\n");
	}
	if (map->ceiling_color)
	{
		ceiling_color = ((map->ceiling_color[0] << 16)
				| (map->ceiling_color[1] << 8) | (map->ceiling_color[2]));
	}
	else
	{
		printf("Warning: Invalid ceiling color.\n");
		return ;
	}
	paint_floor_ceiling(game, floor_color, ceiling_color);
}

void draw_meme_gun(t_game *game)
{
    int gun_width = 200;
    int gun_height = 150;
    int start_x = (game->screen_w - gun_width) / 2;
    int start_y = game->screen_h - gun_height - 40; // Alza un po' l'arma

    // Colori base
    int metal_color = 0x7A7A7A;    // Grigio metallico
    int grip_color = 0x2D2D2D;     // Grigio scuro
    int barrel_color = 0x5A5A5A;   // Grigio medio
    //int accent_color = 0xFFD700;   // Oro per dettagli

    // Parte principale (corpo)
    for (int y = 0; y < gun_height * 0.7; y++) {
        for (int x = gun_width * 0.2; x < gun_width * 0.8; x++) {
            my_pixel_put(start_x + x, start_y + y, game, metal_color);
        }
    }

    // Impugnatura (angolo stile mitra)
    for (int y = gun_height * 0.4; y < gun_height; y++) {
        for (int x = 0; x < gun_width * 0.3; x++) {
            my_pixel_put(start_x + x, start_y + y, game, grip_color);
        }
    }

    // Canna (allungata)
    for (int y = gun_height * 0.1; y < gun_height * 0.6; y++) {
        for (int x = gun_width * 0.8; x < gun_width; x++) {
            my_pixel_put(start_x + x, start_y + y, game, barrel_color);
        }
    }

    // Dettagli (crosshair stile ologramma)
    int sight_size = 15;
    int sight_x = start_x + gun_width * 0.9;
    int sight_y = start_y + gun_height * 0.3;
    
    // Cerchio centrale
    for (int i = -sight_size; i <= sight_size; i++) {
        for (int j = -sight_size; j <= sight_size; j++) {
            if (i*i + j*j <= sight_size*sight_size) {
                my_pixel_put(sight_x + i, sight_y + j, game, 0x00FF00); // Verde
            }
        }
    }

    // Testo meme (solo se hai mlx_string_put)
	if (game->mlx && game->win) {
    mlx_string_put(game->mlx, game->win, 
                   start_x + gun_width / 2 - 30, 
                   start_y + 40, // Sposta la scritta più in basso
                   BLACK, "BRRRRT!"); // Usa bianco per maggiore visibilità
}

}

int	draw_loop(t_game *game)
{
	move_player(game->player, game);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
    game->img = mlx_new_image(game->mlx, game->screen_w, game->screen_h);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	if (!game->map)
		print_error("Errore caricamento mappa");
	draw_floor_ceiling(game, game->map);
	raycasting(game);
	draw_map(game, game->map);
	draw_player(game, game->player, 8, GREEN);
	draw_meme_gun(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
