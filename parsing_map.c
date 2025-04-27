/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 23:55:14 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/27 18:18:41 by mabrigo          ###   ########.fr       */
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

void	handle_map_error(char *line, int fd, t_map_data *map, char *message)
{
	if (line)
		free(line);
	if (fd != -1)
		close(fd);
	free_map(map);
	clear_gnl();
	printf("%s", message);
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
	map->world = load_map(av[1], map_start_line, map);
	if (!check_map(map->world, map))
		handle_map_error(NULL, -1, map, "Error\nInvalid map\n");
	calculate_map_dimensions(map);
}
