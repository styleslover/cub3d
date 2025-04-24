/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:12:27 by damoncad          #+#    #+#             */
/*   Updated: 2025/04/24 21:00:17 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_pixel(t_textures *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0xFFFFFF);
	pixel = texture->addr + (y * texture->line_length
			+ x * (texture->bpp / 8));
	return (*(int *)pixel);
}

void	perform_dda(t_raycasting_shit *a, t_map_data *map)
{
	while (!a->hit)
	{
		if (a->side_dist_x < a->side_dist_y)
		{
			a->side_dist_x += a->delta_dist_x;
			a->map_x += a->step_x;
			a->side = 0;
		}
		else
		{
			a->side_dist_y += a->delta_dist_y;
			a->map_y += a->step_y;
			a->side = 1;
		}
		if (a->map_x < 0 || a->map_x >= map->map_width
			|| a->map_y < 0 || a->map_y >= map->map_height)
			a->hit = 1;
		else if (map->world[a->map_y][a->map_x] == '1')
			a->hit = 1;
	}
}

void	set_texture_data(t_raycasting_shit *a, t_game *game)
{
	if (a->side == 0)
	{
		if (a->ray_dir_x > 0)
			a->texture_index = 2;
		else
			a->texture_index = 3;
	}
	else
	{
		if (a->ray_dir_y > 0)
			a->texture_index = 1;
		else
			a->texture_index = 0;
	}
	if (a->side == 0)
		a->wall_x = a->ray_y + a->perp_wall_dist * a->ray_dir_y;
	else
		a->wall_x = a->ray_x + a->perp_wall_dist * a->ray_dir_x;
	a->wall_x -= floor(a->wall_x);
	a->tex_x = (int)(a->wall_x * game->textures[a->texture_index].width);
	if ((a->side == 0 && a->ray_dir_x > 0)
		|| (a->side == 1 && a->ray_dir_y < 0))
		a->tex_x = game->textures[a->texture_index].width - a->tex_x - 1;
}

void	draw_column(t_raycasting_shit *a, t_game *game, int x)
{
	int	y;
	int	tex_y;
	int	color;

	y = a->draw_start;
	while (y < a->draw_end)
	{
		tex_y = (y * 2 - game->screen_h + a->line_height)
			* (game->textures[a->texture_index].height / 2)
			/ a->line_height;
		color = get_texture_pixel(&game->textures[a->texture_index],
				a->tex_x, tex_y);
		my_pixel_put(x, y, game, color);
		y++;
	}
}

void	raycasting(t_game *game)
{
	t_raycasting_shit	*a;
	int					x;

	x = 0;
	while (x < game->screen_w)
	{
		a = game->ps;
		init_ray(a, game, x);
		calc_step_and_side_dist(a);
		perform_dda(a, game->map);
		calc_wall_data(a, game);
		set_texture_data(a, game);
		draw_column(a, game, x);
		x++;
	}
}
