/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santiago <santiago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:03:51 by damoncad          #+#    #+#             */
/*   Updated: 2025/04/12 15:46:50 by santiago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_matrix(char **map)
{
    int i;

    if (!map)
        return;
    
    i = 0;
    while (map[i])
    {
        free(map[i]);
        map[i] = NULL;
        i++;
    }
    free(map);
}

void free_map(t_map_data *map)
{
    if (!map)
        return;

    if (map->world)
    {
        free_matrix(map->world);
        map->world = NULL;
    }
    
    // Libera i path delle texture solo se non sono NULL
    if (map->north_txtr)
    {
        free(map->north_txtr);
        map->north_txtr = NULL;
    }
    if (map->south_txtr)
    {
        free(map->south_txtr);
        map->south_txtr = NULL;
    }
    if (map->west_txtr)
    {
        free(map->west_txtr);
        map->west_txtr = NULL;
    }
    if (map->east_txtr)
    {
        free(map->east_txtr);
        map->east_txtr = NULL;
    }
    
    // Libera i colori
    if (map->floor_color)
    {
        free(map->floor_color);
        map->floor_color = NULL;
    }
    if (map->ceiling_color)
    {
        free(map->ceiling_color);
        map->ceiling_color = NULL;
    }
}

void free_textures(t_game *game)
{
    int i;

    if (!game || !game->mlx)
        return;

    for (i = 0; i < 4; i++)
    {
        if (game->textures[i].img)
        {
            mlx_destroy_image(game->mlx, game->textures[i].img);
            game->textures[i].img = NULL;
        }
    }
}

// In free_shit.c - Migliorare free_game_resources per liberare tutto correttamente
void free_game_resources(t_game *game)
{
    if (!game)
        return;

    printf("Freeing resources...\n");
    
    // 1. Libera textures per prime (dipende da mlx)
    free_textures(game);
    
    // 2. Libera l'immagine principale
    if (game->img && game->mlx)
    {
        mlx_destroy_image(game->mlx, game->img);
        game->img = NULL;
        game->data = NULL;  // Importante: resetta anche il puntatore ai dati
    }
    
    // 3. Libera la finestra (prima di mlx_display)
    if (game->win && game->mlx)
    {
        mlx_destroy_window(game->mlx, game->win);
        game->win = NULL;
    }
    
    // 4. Libera la mappa e il player
    if (game->map)
    {
        free_map(game->map);
        game->map = NULL;
    }
    
    if (game->player)
    {
        free(game->player);
        game->player = NULL;
    }
    
    // 5. Libera MLX
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        game->mlx = NULL;
    }
    
    printf("Risorse liberate correttamente.\n");
}

