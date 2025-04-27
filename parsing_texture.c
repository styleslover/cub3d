/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 23:48:54 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/27 18:39:11 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_texture(char **txtr, char *value)
{
	if (*txtr)
	{
		free(value);
		free(*txtr);
		*txtr = NULL;
	}
	else
		*txtr = value;
}

void	handle_texture_error(t_map_data *map, char *line, int fd)
{
	free(line);
	handle_config_error(fd, map,
		"Error\nInvalid texture path\n");
}

void	check_texture_duplicate(t_map_data *map, char *str, int fd)
{
	if ((ft_strncmp(str, "NO ", 3) == 0 && map->north_txtr)
		|| (ft_strncmp(str, "SO ", 3) == 0 && map->south_txtr)
		|| (ft_strncmp(str, "WE ", 3) == 0 && map->west_txtr)
		|| (ft_strncmp(str, "EA ", 3) == 0 && map->east_txtr))
		handle_texture_error(map, str, fd);
}

void	validate_and_assign_texture(t_map_data *map,
	int fd, char *str, char *path)
{
	if (!is_valid_texture_path(path))
	{
		free(path);
		free(str);
		handle_config_error(fd, map, "Error\nInvalid texture file\n");
	}
	if (!ft_strncmp(str, "NO ", 3))
		assign_texture(&map->north_txtr, path);
	else if (!ft_strncmp(str, "SO ", 3))
		assign_texture(&map->south_txtr, path);
	else if (!ft_strncmp(str, "WE ", 3))
		assign_texture(&map->west_txtr, path);
	else
		assign_texture(&map->east_txtr, path);
}

void	handle_texture(t_map_data *map, int fd, char *str, int offset)
{
	char	*raw;
	char	*path;

	check_texture_duplicate(map, str, fd);
	raw = extract_raw_path(str, offset, fd, map);
	path = trim_texture_path(raw, str, fd, map);
	validate_and_assign_texture(map, fd, str, path);
}
