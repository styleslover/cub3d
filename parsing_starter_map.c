/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_starter_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 00:06:53 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/25 00:07:31 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_line(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'))
		i++;
	if (!str[i])
		return (0);
	if (str[i] == '1' || str[i] == '0' || str[i] == 'N'
		|| str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
	{
		if (!ft_strncmp(&str[i], "NO ", 3) || !ft_strncmp(&str[i], "SO ", 3)
			|| !ft_strncmp(&str[i], "WE ", 3) || !ft_strncmp(&str[i], "EA ", 3)
			|| !ft_strncmp(&str[i], "F ", 2) || !ft_strncmp(&str[i], "C ", 2))
			return (0);
		return (1);
	}
	return (0);
}

char	**set_map(int map_start_line, char *av, int *fd)
{
	int		lines;
	char	**map;

	*fd = open(av, O_RDONLY);
	if (*fd < 0)
		return (NULL);
	lines = count_lines(av, *fd);
	if (lines <= 0)
	{
		close(*fd);
		return (NULL);
	}
	map = malloc((lines - map_start_line + 1) * sizeof(char *));
	if (!map)
	{
		close(*fd);
		return (NULL);
	}
	return (map);
}

void	skip_to_map_start(int fd, int map_start_line)
{
	char	*line;
	int		i;

	i = 0;
	while (i < map_start_line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		i++;
	}
}

int	get_map(char **map, int fd, int map_start_line)
{
	char	*line;
	int		i;

	skip_to_map_start(fd, map_start_line);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line) || is_empty_line(line))
		{
			map[i] = trim_newline(line);
			i++;
		}
		else
			free(line);
		line = get_next_line(fd);
	}
	map[i] = NULL;
	return (i);
}

char	**load_map(char *av, int map_start_line)
{
	int		fd;
	char	**map;

	map = set_map(map_start_line, av, &fd);
	if (!map)
		return (NULL);
	if (get_map(map, fd, map_start_line) == 0)
	{
		free(map);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (map);
}

