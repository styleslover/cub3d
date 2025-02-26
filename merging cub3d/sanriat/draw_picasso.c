/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_picasso.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:57:35 by damoncad          #+#    #+#             */
/*   Updated: 2025/02/26 17:51:54 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//preso

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
	end_x = player->x + cosf(player->dir) * length;	//il cosf e' per i float
	end_y = player->y + sinf(player->dir) * length;	//il sinf e' per i float
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
//preso
void	draw_player(t_game *game, t_player *player, int size, int color)
{
	int		i;
	int		j;
	float	half_size;
	int		center_x;
	int		center_y;
	float	x;
	float	y;

	// Calcola il centro del quadrato (personaggio)
	center_x = player->x;
	center_y = player->y;
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
	draw_direction_line(game, player, size * 2, GREEN);	//linea verde

	// draw_square(center_x - size / 2, center_y - size / 2, size, game, color);

	// // Disegna la linea di direzione
	// draw_direction_line(game, player, size * 2, GREEN); // Linea verde
}
//inutile
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

//preso
//GRIGLIA DI DEBUG
void	draw_grid(t_game *game, int tile_size)
{
	int	x;
	int	y;

	// Linee orizzontali
	y = game->offset_y;
	while (y < game->offset_y + game->map_height * tile_size)
	{
		x = game->offset_x;
		while (x < game->offset_x + game->map_width * tile_size)
		{
			my_pixel_put(x, y, game, 0xFFFFFF);  // Linea orizzontale bianca
			x++;
		}
		y += tile_size;
	}

	// Linee verticali
	x = game->offset_x;
	while (x < game->offset_x + game->map_width * tile_size)
	{
		y = game->offset_y;
		while (y < game->offset_y + game->map_height * tile_size)
		{
			my_pixel_put(x, y, game, 0xFFFFFF);  // Linea verticale bianca
			y++;
		}
		x += tile_size;
	}
}
//preso
void	draw_map(t_game *game)
{
	char	**map;
	int		color;
	int		i;
	int		j;

	map = game->map;
	game->map_width = (ft_strlen(map[0]) - 1);
	game->map_height = 0;
	while (map[game->map_height] != NULL)
		game->map_height++;

	game->offset_x = (WIDTH - game->map_width * TILE_SIZE) / 2;
	game->offset_y = (HEIGHT - game->map_height * TILE_SIZE) / 2;
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j + 1] != '\0')
		{
			if (map[i][j] == '1')
				color = RED;
			else if (map[i][j] == '0')
				color = BLUE;
			else if (map[i][j] == 'N')	// IGNORA 'N' O GESTISCI IL GIOCATORE
				color = GREEN;
			else
			{
				j++;
				continue;
			}
				draw_square(j * TILE_SIZE + game->offset_x,
				i * TILE_SIZE + game->offset_y, TILE_SIZE, game, color);
			j++;
		}
		i++;
	}
	//AGGIUNGE LA GRIGLIA DI DEBUG
	draw_grid(game, map, TILE_SIZE);
	//printf("map_width: %d\nmap_height%d\n", game->map_width, game->map_height);
}
