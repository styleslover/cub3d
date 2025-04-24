/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 23:48:54 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/24 23:50:06 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_texture(char **txtr, char *value, char *err_msg)
{
	if (*txtr)
	{
		free(value);
		free(*txtr);
		*txtr = NULL;
		print_error(err_msg);
	}
	else
		*txtr = value;
}

int	is_valid_texture_path(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

void	handle_texture_error(t_map_data *map, char *str, int fd)
{
	if ((!ft_strncmp(str, "NO ", 3) && !map->north_txtr)
		|| (!ft_strncmp(str, "SO ", 3) && !map->south_txtr)
		|| (!ft_strncmp(str, "WE ", 3) && !map->west_txtr)
		|| (!ft_strncmp(str, "EA ", 3) && !map->east_txtr))
	{
		handle_config_error(fd, map,
			"Error\nDuplicate texture configuration\n");
	}
}

void	handle_texture(t_map_data *map, int fd, char *str, int offset)
{
	char	*path;

	path = strcmp_from_i(offset, str);
	if (!path)
	{
		handle_config_error(fd, map, "Error: Invalid texture path format\n");
		return ;
	}
	if (!is_valid_texture_path(path))
	{
		free(path);
		handle_config_error(fd, map, "Error\nInvalid texture path\n");
		return ;
	}
	if (!ft_strncmp(str, "NO ", 3))
		assign_texture(&map->north_txtr, path, "Error\nDuplicate NO texture\n");
	else if (!ft_strncmp(str, "SO ", 3))
		assign_texture(&map->south_txtr, path, "Error\nDuplicate SO texture\n");
	else if (!ft_strncmp(str, "WE ", 3))
		assign_texture(&map->west_txtr, path, "Error\nDuplicate WE texture\n");
	else if (!ft_strncmp(str, "EA ", 3))
		assign_texture(&map->east_txtr, path, "Error\nDuplicate EA texture\n");
	handle_texture_error(map, str, fd);
}
