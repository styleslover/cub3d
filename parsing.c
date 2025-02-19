/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:47:17 by mabrigo           #+#    #+#             */
/*   Updated: 2025/02/19 21:31:22 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_map *map)
{
	map->map_height = 0;
	map->map_width = 0;
	map->east_txtr = NULL;
	map->north_txtr = NULL;
	map->south_txtr = NULL;
	map->west_txtr = NULL;
	map->ceiling_color = NULL;
	map->floor_color = NULL;
}

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
	return (dest);
}


void	parse_config_line(char *str, t_map *map)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (ft_strncmp(str, "NO ", 3) == 0)
		map->north_txtr = strcmp_from_i(i, str);
	else if (ft_strncmp(str, "SO ", 3) == 0)
		map->south_txtr = strcmp_from_i(i, str);
	else if (ft_strncmp(str, "WE ", 3) == 0)
		map->west_txtr = strcmp_from_i(i, str);
	else if (ft_strncmp(str, "EA ", 3) == 0)
		map->east_txtr = strcmp_from_i(i, str);
	else if (ft_strncmp(str, "F ", 2) == 0)
		map->floor_color = strcmp_from_i(i, str);
	else if (ft_strncmp(str, "C ", 2) == 0)
		map->ceiling_color = strcmp_from_i(i, str);
}

int	is_map_line(char *str)
{
	if (!*str)
		return (0);
	while (*str && *str == ' ')
		str++;
	if (*str != '1' && *str != '0' && *str != 'N'
		&& *str != 'S' && *str != 'E' && *str != 'W')
		return (0);
	return (1);
}

void	parse_file(int fd, t_map *map)
{
	char	*line;
	int		line_len;

	line = get_next_line(fd);
	map->map_width = 0;
	map->map_height = 0;
	line_len = 0;
	while (line)
	{
		if (is_map_line(line) != 0)
		{
			line_len = ft_strlen(line);
			if (line_len > map->map_width)
			map->map_width = line_len;
			map->map_height++;
		}
		else
			parse_config_line(line, map);
		free(line);
		line = get_next_line(fd);
	}
	map->map_width *= 64;
	map->map_height *= 64;
	printf("North Texture: %s\n", map->north_txtr);
	printf("South Texture: %s\n", map->south_txtr);
	printf("West Texture: %s\n", map->west_txtr);
	printf("East Texture: %s\n", map->east_txtr);
	printf("Floor Color: %s\n", map->floor_color);
	printf("Ceiling Color: %s\n", map->ceiling_color);
	printf("Map Size: %d x %d\n", map->map_width, map->map_height);

}
