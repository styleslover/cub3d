/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_picasso.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-18 15:57:35 by damoncad          #+#    #+#             */
/*   Updated: 2025-02-18 15:57:35 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(int x, int y, int size, t_game *game, int color, bool is_player)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (is_player)
				my_pixel_put(x + j, y + i, game, color);
			else
				my_pixel_put(x + j, y + i, game, color);
			j++;
		}
		i++;
	}
}

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
				i * TILE_SIZE + game->offset_y, TILE_SIZE, game, color, false);
			j++;
		}
		i++;
	}
	//AGGIUNGE LA GRIGLIA DI DEBUG
	draw_grid(game, TILE_SIZE);
	//printf("map_width: %d\nmap_height%d\n", game->map_width, game->map_height);
}
