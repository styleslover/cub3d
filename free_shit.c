/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:03:51 by damoncad          #+#    #+#             */
/*   Updated: 2025/04/09 19:21:37 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_matrix(char **map)
{
	int	i;

    if (map)
    {
        i = 0;
        while (map[i])
            free(map[i++]);
        free(map);
    }
}

void	free_map(t_map_data *map)
{
	int i;

    if (map->world)
    {
        i = 0;
        while (map->world[i])
            free(map->world[i++]);
        free(map->world);
    }
    
}

void	free_mlx(t_game *game)
{
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);	
	}
}

void	free_game_resources(t_game *game)
{
    printf("Liberando risorse...\n");
    if (!game)
        return;
    if (game->mlx)
    {
        for (int i = 0; i < 4; i++)
        {
            if (game->textures[i].img)
                mlx_destroy_image(game->mlx, game->textures[i].img);
        }
    }
    if (game->player)
    {
        free(game->player);
        game->player = NULL;
    }
    if (game->map)
    {
        free_map(game->map);
        game->map = NULL;
    }
    if (game->img)
    {
		mlx_destroy_image(game->mlx, game->img);
        game->img = NULL;
    }
    if (game->win)
    {
		mlx_destroy_window(game->mlx, game->win);
        game->win = NULL;
    }
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        game->mlx = NULL;
    }
    printf("Risorse liberate correttamente.\n");
}

