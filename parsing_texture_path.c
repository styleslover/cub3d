/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:38:19 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/27 20:42:24 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
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
	if (!validate_xpm_header(path))
	{
		return (0);
	}
	return (1);
}

char	*extract_raw_path(char *str, int offset,
	int fd, t_map_data *map)
{
	char	*raw;

	if (!str[offset] || str[offset] == '\n')
	{
		free(str);
		handle_config_error(fd, map, "Error\nMissing texture path\n");
	}
	raw = strcmp_from_i(offset, str);
	if (!raw)
	{
		free(str);
		handle_config_error(fd, map, "Error\nMemory allocation failed\n");
	}
	return (raw);
}

char	*trim_texture_path(char *raw)
{
	char	*path;

	if (!raw || raw[0] == '\0')
	{
		if (raw)
			free(raw);
		return (NULL);
	}
	path = ft_strtrim(raw, " \t\r\n");
	free(raw);
	if (!path || path[0] == '\0')
	{
		if (path)
			free(path);
		return (NULL);
	}
	return (path);
}
