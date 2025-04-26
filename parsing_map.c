/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 23:55:14 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/26 17:38:35 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_map_line(char *line, int current_line, int *map_start_line)
{
	if (is_map_line(line) != 0)
	{
		if (*map_start_line == 0)
			*map_start_line = current_line - 1;
		return (1);
	}
	return (0);
}

void	handle_map_error(char *line, int fd, t_map_data *map)
{
	free(line);
	close(fd);
	free_map(map);
	clear_gnl();
	printf("Error\nInvalid map line\n");
	clear_gnl();
	exit(1);
}

void	calculate_map_dimensions(t_map_data *map)
{
	while (map->world[map->map_height])
	{
		if (ft_strlen(map->world[map->map_height]) > map->map_width)
			map->map_width = ft_strlen(map->world[map->map_height]);
		map->map_height++;
	}
}

void	load_and_check_map(char **av, t_map_data *map, int map_start_line)
{
	map->world = load_map(av[1], map_start_line);
	if (!map->world)
	{
		printf("Error\nFailed to load map\n");
		free_map(map);
		exit(1);
	}
	if (!check_map(map->world))
	{
		printf("Error\nInvalid map\n");
		free_map(map);
		exit(1);
	}
	calculate_map_dimensions(map);
}
