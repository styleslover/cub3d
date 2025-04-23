/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:12:27 by damoncad          #+#    #+#             */
/*   Updated: 2025/04/23 14:53:54 by damoncad         ###   ########.fr       */
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

void	init_raycasting_shit(t_raycasting_shit *ps)
{
	ps->camera_x = 0;
	ps->ray_dir_x = 0;
	ps->ray_dir_y = 0;
	ps->ray_x = 0;
	ps->ray_y = 0;
	ps->map_x = 0;
	ps->map_y = 0;
	ps->delta_dist_x = 0;
	ps->delta_dist_y = 0;
	ps->side_dist_x = 0;
	ps->side_dist_y = 0;
	ps->step_x = 0;
	ps->step_y = 0;
	ps->hit = 0;
	ps->side = 0;
	ps->perp_wall_dist = 0;
	ps->line_height = 0;
	ps->draw_start = 0;
	ps->draw_end = 0;
	ps->texture_index = 0;
	ps->wall_x = 0.0;
	ps->tex_x = 0;
}

void	init_ray(t_raycasting_shit *a, t_game *game, int x)
{
	t_player	*p;
	t_map_data	*map;

	p = game->player;
	map = game->map;
	a->camera_x = 2 * x / (double)game->screen_w - 1;
	a->ray_dir_x = p->dir_x + p->plane_x * a->camera_x;
	a->ray_dir_y = p->dir_y + p->plane_y * a->camera_x;
	a->ray_x = (p->x - map->offset_x) / TILE_SIZE;
	a->ray_y = (p->y - map->offset_y) / TILE_SIZE;
	a->map_x = (int)a->ray_x;
	a->map_y = (int)a->ray_y;
	a->delta_dist_x = fabs(1 / a->ray_dir_x);
	a->delta_dist_y = fabs(1 / a->ray_dir_y);
	a->hit = 0;
}

void	calc_step_and_side_dist(t_raycasting_shit *a)
{
	if (a->ray_dir_x < 0)
	{
		a->step_x = -1;
		a->side_dist_x = (a->ray_x - a->map_x) * a->delta_dist_x;
	}
	else
	{
		a->step_x = 1;
		a->side_dist_x = (a->map_x + 1.0 - a->ray_x) * a->delta_dist_x;
	}
	if (a->ray_dir_y < 0)
	{
		a->step_y = -1;
		a->side_dist_y = (a->ray_y - a->map_y) * a->delta_dist_y;
	}
	else
	{
		a->step_y = 1;
		a->side_dist_y = (a->map_y + 1.0 - a->ray_y) * a->delta_dist_y;
	}
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

void	calc_wall_data(t_raycasting_shit *a, t_game *game)
{
	if (a->side == 0)
		a->perp_wall_dist = (a->map_x - a->ray_x
				+ (1 - a->step_x) / 2) / a->ray_dir_x;
	else
		a->perp_wall_dist = (a->map_y - a->ray_y
				+ (1 - a->step_y) / 2) / a->ray_dir_y;
	a->line_height = (int)(game->screen_h / a->perp_wall_dist);
	a->draw_start = -a->line_height / 2 + game->screen_h / 2;
	if (a->draw_start < 0)
		a->draw_start = 0;
	a->draw_end = a->line_height / 2 + game->screen_h / 2;
	if (a->draw_end >= game->screen_h)
		a->draw_end = game->screen_h - 1;
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
	int				x;

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
