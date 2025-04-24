/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:52:13 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/24 19:50:36 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	check_filename(char *av)
{
	int	len;

	len = ft_strlen(av);
	if (!av)
		return (0);
	if (ft_strncmp(av + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

void	check_fd_not_directory(char *str)
{
	int		fd;

	fd = open(str, __O_DIRECTORY);
	if (fd != -1)
	{
		printf("Error: path is a directory\n");
		exit(1);
	}
}

void	free_game_resources(t_game *game)
{
	if (!game)
		return ;
	printf("Freeing resources...\n");
	free_textures(game);
	if (game->img && game->mlx)
	{
		mlx_destroy_image(game->mlx, game->img);
		game->img = NULL;
	}
	if (game->win && game->mlx)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	free_game_resources_help(game);
	printf("Risorse liberate correttamente.\n");
}

int	main(int ac, char **av)
{
	t_game			game;
	t_map_data		map;

	if (ac != 2)
		return (printf("Error, please check your input"));
	if (!check_filename(av[1]))
		return (printf("Error: invalid type of fd\n"));
	map.fd = open(av[1], O_RDONLY);
	if (map.fd == -1)
		return (printf("Error: invalid fd"));
	check_fd_not_directory(av[1]);
	parse_file(av, map.fd, &map);
	close(map.fd);
	init_game(av[1], &game, &map);
	draw_map(&game, &map);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	free_game_resources(&game);
	return (0);
}
