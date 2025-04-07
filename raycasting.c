/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:12:27 by damoncad          #+#    #+#             */
/*   Updated: 2025/04/07 19:57:16 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_texture_pixel(t_textures *texture, int x, int y)
{
    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height) 
    return 0xFFFFFF; // Colore di debug (bianco)

    char *pixel = texture->addr + (y * texture->line_length + 
                                  x * (texture->bpp / 8));
    return *(int *)pixel;
}

void raycasting(t_game *game)
{
    t_player *p = game->player;
    t_map_data *map = game->map;

    for (int x = 0; x < game->screen_w; x++)
    {
        // 1. Calcolo direzione del raggio
        double camera_x = 2 * x / (double)game->screen_w - 1; // Range: [-1, 1]
        double ray_dir_x = p->dir_x + p->plane_x * camera_x;
        double ray_dir_y = p->dir_y + p->plane_y * camera_x;

        // 2. Posizione iniziale (in coordinate mappa)
        double ray_x = (p->x - map->offset_x) / TILE_SIZE;
        double ray_y = (p->y - map->offset_y) / TILE_SIZE;

        // 3. DDA Algorithm
        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);
        
        int map_x = (int)ray_x;
        int map_y = (int)ray_y;
        
        double side_dist_x, side_dist_y;
        int step_x, step_y;
        int hit = 0;
        int side; // 0 = x-side, 1 = y-side

        // Calcolo step e side_dist iniziale
        if (ray_dir_x < 0) {
            step_x = -1;
            side_dist_x = (ray_x - map_x) * delta_dist_x;
        } else {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - ray_x) * delta_dist_x;
        }
        if (ray_dir_y < 0) {
            step_y = -1;
            side_dist_y = (ray_y - map_y) * delta_dist_y;
        } else {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - ray_y) * delta_dist_y;
        }

        // Lancio del raggio
        while (hit == 0) {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            // Controllo collisione con muro o uscita dalla mappa
            if (map_x < 0 || map_x >= map->map_width || 
                map_y < 0 || map_y >= map->map_height)
            {
                hit = 1; // Raggio uscito dalla mappa
            }
            else if (map->world[map_y][map_x] == '1')
            {
                hit = 1; // Muro colpito
            }
        }

        // 4. Calcolo distanza (senza fisheye)
        double perp_wall_dist;
        if (side == 0)
            perp_wall_dist = (map_x - ray_x + (1 - step_x) / 2) / ray_dir_x;
        else
            perp_wall_dist = (map_y - ray_y + (1 - step_y) / 2) / ray_dir_y;
       
        // [5] Calcolo altezza linea da disegnare
        int line_height = (int)(game->screen_h / perp_wall_dist);
        int draw_start = -line_height / 2 + game->screen_h / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + game->screen_h / 2;
        if (draw_end >= game->screen_h) draw_end = game->screen_h - 1;

        int texture_index;

        if (side == 0)
            texture_index = (ray_dir_x > 0 ? 2 : 3);
        else
            texture_index = (ray_dir_y > 0 ? 1 : 0);
        // [6] Calcolo coordinate texture
        float wall_x;
        if (side == 0)
            wall_x = ray_y + perp_wall_dist * ray_dir_y;
        else
            wall_x = ray_x + perp_wall_dist * ray_dir_x;
        wall_x -= floor(wall_x);

        int tex_x = (int)(wall_x * (double)game->textures[texture_index].width);
        if (side == 0 && ray_dir_x > 0) tex_x = game->textures[texture_index].width - tex_x - 1;
        if (side == 1 && ray_dir_y < 0) tex_x = game->textures[texture_index].width - tex_x - 1;

        // [7] Disegno della linea verticale con texture
        for (int y = draw_start; y < draw_end; y++)
        {
            int tex_y = (y * 2 - game->screen_h + line_height) * 
                       (game->textures[0].height / 2) / line_height;
            int color = get_texture_pixel(&game->textures[texture_index], tex_x, tex_y);
            my_pixel_put(x, y, game, color);
        }
    }
}
