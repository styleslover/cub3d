/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariel <mariel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:52:13 by mabrigo           #+#    #+#             */
/*   Updated: 2025/02/25 00:10:08 by mariel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_error(char *str)
{
	printf("%s", str);
	exit(0);
}

int	main(int ac, char **av)
{
	t_game			game;
	t_map_data		map;

	if (ac != 2)
		return (printf("Error, please check your input"));
	map.fd = open(av[1], O_RDONLY);
	if (map.fd == -1)
		return (printf("Error: invalid fd"));
	parse_file(av, map.fd, &map);
	close(map.fd);
	init_game(&game, &map);
	printf("SONO QUI\n");
	draw_map(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	free(game.player); //testing
	return (0);
}
