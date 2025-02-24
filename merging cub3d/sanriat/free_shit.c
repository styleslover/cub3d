/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-18 13:03:51 by damoncad          #+#    #+#             */
/*   Updated: 2025-02-18 13:03:51 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
    if (!map)
    {
        return;
    }
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
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

