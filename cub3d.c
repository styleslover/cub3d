/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:52:13 by mabrigo           #+#    #+#             */
/*   Updated: 2025/02/24 19:20:15 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game		game;
	t_map		map;

	if (ac != 2)
		print_error("NOT ENOUGH ARGUMENTS");
	map.fd = open(av[1], O_RDONLY);
	if (map.fd == -1)
		printf("Error: invalid fd");
	game.map = load_map(map.fd);
	parse_file(map.fd, &map);
	close(map.fd);
	init_game(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	free(game.player);
	return (0);
}