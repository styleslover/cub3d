/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_starter_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 00:06:53 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/26 19:06:43 by damoncad         ###   ########.fr       */
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

char	**set_map(int map_start_line, char *av, int *fd, t_map_data *map_data)
{
	int		lines;
	char	**map_arr;

	*fd = open(av, O_RDONLY);
	if (*fd < 0)
		handle_map_error(NULL, *fd, map_data, "Error\nFailed to open file\n");
	lines = count_lines(av, *fd);
	if (lines <= 0)
	{
		close(*fd);
		handle_map_error(NULL, *fd, map_data, "Error\nEmpty map file\n");
	}
	map_arr = malloc((lines - map_start_line + 1) * sizeof(char *));
	if (!map_arr)
	{
		close(*fd);
		handle_map_error(NULL, *fd, map_data, "Error\nMemory allocation failed\n");
	}
	return (map_arr);
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

char	**load_map(char *av, int map_start_line, t_map_data *map_data)
{
	int		fd;
	char	**map_arr;

	map_arr = set_map(map_start_line, av, &fd, map_data);
	if (get_map(map_arr, fd, map_start_line) == 0)
	{
		free(map_arr);
		close(fd);
		handle_map_error(NULL, fd, map_data, "Error\nNo map found\n");
	}
	close(fd);
	return (map_arr);
}

