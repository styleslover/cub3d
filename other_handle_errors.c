/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_handle_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:51:06 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/27 20:04:45 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_player_error(t_player *player, t_map_data *map, char *message)
{
	if (player)
		free(player);
	free_map(map);
	clear_gnl();
	printf("%s", message);
	exit(1);
}

void	handle_config_error(int fd, t_map_data *map, char *message)
{
	close(fd);
	free_map(map);
	clear_gnl();
	printf("%s", message);
	exit (1);
}

void	handle_config_line(char *line, t_map_data *map,
	int fd, int *config_done)
{
	if (is_map_line(line))
	{
		free(line);
		handle_config_error(fd, map,
			"Error\nInvalid configuration line\n");
	}
	else
	{
		parse_config_line(line, map, fd);
		if (map->north_txtr && map->south_txtr && map->west_txtr
			&& map->east_txtr && map->floor_color && map->ceiling_color)
			*config_done = 1;
	}
}
