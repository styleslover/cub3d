/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:30:39 by mariel            #+#    #+#             */
/*   Updated: 2025/04/23 20:25:48 by damoncad         ###   ########.fr       */
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

void	draw_direction_line(t_game *game, t_player *player,
		int length, int color)
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

	end_x = player->x + player->dir_x * length;
	end_y = player->y + player->dir_y * length;
	delta_x = end_x - player->x;
	delta_y = end_y - player->y;
	max_steps = (int)fmaxf(fabsf(delta_x), fabsf(delta_y));
	step_x = delta_x / max_steps;
	step_y = delta_y / max_steps;
	temp_x = player->x;
	temp_y = player->y;
	i = 0;
	while (i <= max_steps)
	{
		my_pixel_put((int)temp_x, (int)temp_y, game, color);
		temp_x += step_x;
		temp_y += step_y;
		i++;
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

void	draw_player(t_game *game, t_player *player, int size, int color)
{
	int		i;
	int		j;
	float	half_size;
	int		center_x;
	int		center_y;

	center_x = (player->x - game->map->offset_x)
		* MINIMAP_SIZE / TILE_SIZE + game->map->offset_minimap_x;
	center_y = (player->y - game->map->offset_y)
		* MINIMAP_SIZE / TILE_SIZE + game->map->offset_minimap_y;
	half_size = size / 2.0f;
	i = -half_size;
	while (i <= half_size)
	{
		j = -half_size;
		while (j <= half_size)
		{
			player->rx = center_x + j;
			player->ry = center_y + i;
			rotate_point(player, center_x, center_y, player->dir);
			my_pixel_put((int)player->rx, (int)player->ry, game, color);
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

	if (!map->world || !map->world[0])
	{
		printf("Error: Map not loaded or empty\n");
		return ;
	}
	map->offset_minimap_x = game->screen_w
		- (map->map_width * MINIMAP_SIZE) - 120;
	map->offset_minimap_y = game->screen_h
		- (map->map_height * MINIMAP_SIZE) - 120;
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
				color = WHITE;
			else
			{
				j++;
				continue ;
			}
			draw_square(j * MINIMAP_SIZE + map->offset_minimap_x,
				i * MINIMAP_SIZE + map->offset_minimap_y,
				MINIMAP_SIZE, game, color);
			j++;
		}
		i++;
	}
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
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
