/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:30:39 by mariel            #+#    #+#             */
/*   Updated: 2025/04/26 15:05:22 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		printf("Error\nInvalid floor color\n");
	}
	if (map->ceiling_color)
	{
		ceiling_color = ((map->ceiling_color[0] << 16)
				| (map->ceiling_color[1] << 8) | (map->ceiling_color[2]));
	}
	else
	{
		printf("Error\nInvalid ceiling color.\n");
		return ;
	}
	paint_floor_ceiling(game, floor_color, ceiling_color);
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
		print_error("Error\nErrore caricamento mappa\n");
	draw_floor_ceiling(game, game->map);
	raycasting(game);
	draw_map(game, game->map);
	game->color_player = GREEN;
	draw_player(game, game->player, 8);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
