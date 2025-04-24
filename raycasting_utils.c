/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:59:28 by damoncad          #+#    #+#             */
/*   Updated: 2025/04/24 21:00:20 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
