/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 23:48:54 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/26 17:37:03 by damoncad         ###   ########.fr       */
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

int	validate_xpm_header(char *texture_path)
{
    int		fd;
    int		values[4];
    int		valid;
    char	*line;

    fd = open(texture_path, O_RDONLY);
    if (fd < 0)
        return (0);
    valid = find_xpm_header(fd, values);
    while ((line = get_next_line(fd)))
        free(line);
    close(fd);
    return (valid);
}

int	is_valid_texture_path(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);

	if (ft_strnstr(path, ".xpm", ft_strlen(path)))
	{
		if (!validate_xpm_header(path))
			return (0);
	}
	return (1);
}


void	test_texture_error_handler(t_map_data *map, char *line, int fd)
{
	free(line);
	handle_config_error(fd, map,
		"Error\nInvalid texture path\n");
}

void	handle_texture_error(t_map_data *map, char *str, int fd)
{
	if ((!ft_strncmp(str, "NO ", 3) && !map->north_txtr)
		|| (!ft_strncmp(str, "SO ", 3) && !map->south_txtr)
		|| (!ft_strncmp(str, "WE ", 3) && !map->west_txtr)
		|| (!ft_strncmp(str, "EA ", 3) && !map->east_txtr))
		test_texture_error_handler(map, str, fd);
}

void	handle_texture(t_map_data *map, int fd, char *str, int offset)
{
	char	*path;
	
	handle_texture_error(map, str, fd);
	path = strcmp_from_i(offset, str);
	if (!path)
	{
		handle_config_error(fd, map, "Error\nMissing texture path\n");
		return ;
	}
	if (!is_valid_texture_path(path))
	{
		free(path);
		handle_config_error(fd, map, "Error\nInvalid texture file\n");
		return ;
	}
	if (!ft_strncmp(str, "NO ", 3))
	assign_texture(&map->north_txtr, path);
	else if (!ft_strncmp(str, "SO ", 3))
	assign_texture(&map->south_txtr, path);
	else if (!ft_strncmp(str, "WE ", 3))
	assign_texture(&map->west_txtr, path);
	else if (!ft_strncmp(str, "EA ", 3))
		assign_texture(&map->east_txtr, path);
}
