/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariel <mariel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 22:52:55 by mariel            #+#    #+#             */
/*   Updated: 2025/03/16 19:38:05 by mariel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*strcmp_from_i(int i, char *src)
{
	int		j;
	int		len;
	char	*dest;

	if (!src)
		return (NULL);
	len = ft_strlen(src) - i + 1;
	if (len <= 0)
		return (NULL);
	dest = malloc(sizeof(char) * len);
	if (!dest)
		return (NULL);
	j = 0;
	while (src[i])
		dest[j++] = src[i++];
	dest[j] = '\0';
	dest = ft_strtrim(dest, " ");
	return (dest);
}

void	parse_config_line(char *str, t_map_data *map)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (ft_strncmp(str, "NO ", 3) == 0)
		map->north_txtr = strcmp_from_i(i + 3, str);
	else if (ft_strncmp(str, "SO ", 3) == 0)
		map->south_txtr = strcmp_from_i(i + 3, str);
	else if (ft_strncmp(str, "WE ", 3) == 0)
		map->west_txtr = strcmp_from_i(i + 3, str);
	else if (ft_strncmp(str, "EA ", 3) == 0)
		map->east_txtr = strcmp_from_i(i + 3, str);
	else if (ft_strncmp(str, "F ", 2) == 0)
		map->floor_color = strcmp_from_i(i + 2, str);
	else if (ft_strncmp(str, "C ", 2) == 0)
		map->ceiling_color = strcmp_from_i(i + 2, str);
}

int	is_map_line(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!str[i])
		return (0);
	if (str[i] == '1' || str[i] == '0' || str[i] == 'N'
		|| str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
	{
		if (ft_strncmp(&str[i], "NO ", 3) == 0 || ft_strncmp(&str[i], "SO ", 3) == 0
			|| ft_strncmp(&str[i], "WE ", 3) == 0 || ft_strncmp(&str[i], "EA ", 3) == 0
			|| ft_strncmp(&str[i], "F ", 2) == 0 || ft_strncmp(&str[i], "C ", 2) == 0)
			return (0);
		return (1);
	}
	return (0);
}

int	count_lines(char *av, int fd)
{
	int		lines;
	char	*line;

	lines = 0;
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (0);
	while ((line = get_next_line(fd)))
	{
		lines++;
		free(line);
	}
	close(fd);
	return (lines);
}

// Funzione per caricare la mappa
// char	**load_map(char *av, int fd)
// {
// 	int		i;
// 	int		lines;
// 	char	**map;

//     if (fd < 0)
// 		return (0);
// 	lines = count_lines(av, fd);
// 	if (lines <= 0)
// 		return (NULL);
// 	map = malloc((lines + 1) * sizeof(char *));  // +1 per NULL finale
// 	if (!map)
// 		return (NULL);
// 	fd = open(av, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		free(map);
// 		return (NULL);
// 	}
// 	i = 0;
// 	while (i < lines)
// 	{
// 		map[i] = get_next_line(fd);
// 		if (!map[i])  // Se get_next_line fallisce
// 		{
// 			while (i > 0)
// 				free(map[--i]);
// 			free(map);
// 			close(fd);
// 			return (NULL);
// 		}
// 		printf("Map line %d: %s\n", i, map[i]);//debug
// 		i++;
// 	}
// 	map[i] = NULL;  // Terminatore NULL per l'array di stringhe
// 	close(fd);
// 	// if (check_map(map))
// 	return (map);
// }

// char	**load_map(char *av)
// {
// 	int		fd;
// 	int		i;
// 	int		lines;
// 	char	**map;

// 	fd = open(av, O_RDONLY);
//     if (fd < 0)
// 		return (0);
// 	lines = count_lines(av, fd);
// 	if (lines <= 0)
// 	{
// 		close(fd);
// 		return (NULL);
// 	}
// 	map = malloc((lines + 1) * sizeof(char *));  // +1 per NULL finale
// 	if (!map)
// 	{
// 		close(fd);
// 		return (NULL);
// 	}
// 	fd = open(av, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		free(map);
// 		return (NULL);
// 	}
// 	i = 0;
// 	while (i < lines)
// 	{
// 		map[i] = get_next_line(fd);
// 		if (!map[i])  // Se get_next_line fallisce
// 		{
// 			while (i > 0)
// 				free(map[--i]);
// 			free(map);
// 			close(fd);
// 			return (NULL);
// 		}
// 		printf("Map line %d: %s\n", i, map[i]);//debug
// 		i++;
// 	}
// 	map[i] = NULL;  // Terminatore NULL per l'array di stringhe
// 	close(fd);
// 	// if (check_map(map))
// 	return (map);
// }
char *trim_newline(char *line)
{
	int len = strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return line;
}

char	**load_map(char *av, int *map_start_line)
{
	int		fd;
	int		i;
	int		lines;
	char	**map;
	char	*line;

	fd = open(av, O_RDONLY);
    if (fd < 0)
		return (0);
	lines = count_lines(av, fd);
	if (lines <= 0)
	{
		close(fd);
		return (NULL);
	}
	map = malloc((lines - *map_start_line + 1) * sizeof(char *));  // +1 per NULL finale
	if (!map)
	{
		close(fd);
		return (NULL);
	}
	fd = open(av, O_RDONLY);
	if (fd < 0)
	{
		free(map);
		return (NULL);
	}
	i = 0;
	while (i < *map_start_line)
	{
		line = get_next_line(fd);
		if (!line)  // Se get_next_line fallisce
			break;
		free(line);
		i++;
	}
	i = 0;
	while ((line = get_next_line(fd)))
	{
		if (is_map_line(line))
		{
			map[i] = line;
			map[i] =trim_newline(map[i]);
			i++;
		}
		else
			free(line);
	}
	
	map[i] = NULL;  // Terminatore NULL per l'array di stringhe
	close(fd);
	// if (check_map(map))
	return (map);
}


//rimuove caratteri iniziali e finali di una stringa
int	is_empty_line(char *str)
{
	if (!str)
		return (1);  // Linea nulla è considerata vuota

	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
			return (0);  // La linea non è vuota
		str++;
	}
	return (1);  // La linea è vuota
}


void	parse_file(char **av, int fd, t_map_data *map)
{
	char	*line;
	int		line_len;
	int		config_done;
	int		map_start_line;

	init_map(map);
	line_len = 0;
	config_done = 0;
	map_start_line = 0;
	while ((line = get_next_line(fd)))
	{
		if (is_empty_line(line))
		{
			printf("Ignoring empty line: %s\n", line);
			free(line);
			continue;
		}
		if (config_done)
		{
			if (is_map_line(line) != 0)
			{
				line_len = ft_strlen(line);
				if (line_len > map->win_width)
					map->win_width = line_len;
				map->win_height++;
			}
			else
			{
				printf("Error: invalid line in map: %s\n", line);	//da mettere funz error per tutte
				free(line);
				exit(1);
			}	
		}
		else
		{
			if (is_map_line(line))
			{
				printf("Error: map line before configurations: %s\n", line);
				free(line);
				exit(1);
			}
			else
			{
				parse_config_line(line, map);
				if (map->north_txtr && map->south_txtr && map->west_txtr
					&& map->east_txtr && map->floor_color && map->ceiling_color)
				{
					config_done = 1;
				}
			}
		}
		free(line);
	}
	close(fd);
	map->world = load_map(av[1], &map_start_line);
	if (!check_map(map->world))
	{
		printf("Error: Failed to load map\n");
		exit(1);
	}
	map->win_width *= TILE_SIZE;
	map->win_height *= TILE_SIZE;
	if (map->win_width >= WIDTH || map->win_height >= HEIGHT)
	{
		map->win_width = map->win_width;
		map->win_height = map->win_height;
	}
	printf("North Texture: %s\n", map->north_txtr);
	printf("South Texture: %s\n", map->south_txtr);
	printf("West Texture: %s\n", map->west_txtr);
	printf("East Texture: %s\n", map->east_txtr);
	printf("Floor Color: %s\n", map->floor_color);
	printf("Ceiling Color: %s\n", map->ceiling_color);
	printf("Win Size (pxl): %d x %d\n", map->win_width, map->win_height);
	int i = 0;
	while (map->world[i])
	{
		printf("map line [%d]: %s\n", i, map->world[i]);
		i++;
	}
	
	//map_check(map); //todo: check delle texture (no spazi o altro), check valori f e c, mappa chiusa
}
