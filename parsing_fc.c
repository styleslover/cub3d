/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 23:52:21 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/27 16:36:50 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_fc_format(char *fc,char *line, int fd, t_map_data *map)
{
	int	j;
	int	commas;
	(void)fd;
	(void)map;
	(void)line;
	
	j = 0;
	commas = 0;
	while (fc[j])
	{
		if (fc[j] == ',')
			commas++;
		j++;
	}
	if (commas != 2)
	{
		return (0);
	}
	return (1);
}

int	**get_target_color(int i, char *str, t_map_data *map)
{
	if (ft_strncmp(str + i, "F ", 2) == 0)
	{
		if (map->floor_color)
		{
			free(map->floor_color);
			map->floor_color = NULL;
			return (NULL);
		}
		return (&map->floor_color);
	}
	else if (ft_strncmp(str + i, "C ", 2) == 0)
	{
		if (map->ceiling_color)
		{
			free(map->ceiling_color);
			map->ceiling_color = NULL;
			return (NULL);
		}
		return (&map->ceiling_color);
	}
	return (NULL);
}

void	handle_invalid_color(int fd, t_map_data *map, char *message)
{
	if (fd >= 0)
		close(fd);
	free_map(map);
	clear_gnl();
	print_error(message);
	exit(1);
}

void	parse_floor_ceiling(int i, char *str, t_map_data *map, int fd)
{
    char	*fc;
    int	**target;
    int	 *values;

    target = get_target_color(i, str, map);
    if (!target || !str[i + 2])
    {
        free(str);
        handle_invalid_color(fd, map, "Error\nInvalid color line\n");
    }
    fc = strcmp_from_i(i + 2, str);
    if (!fc)
    {
        free(str);
        handle_invalid_color(fd, map, "Error\nInvalid color line\n");
    }
    if (!check_fc_format(fc, str, fd, map))
	{
		free(fc);
		free(str);
		handle_invalid_color(fd, map, "Error\nInvalid RGB format\n");
	}
    values = parse_rgb_values(fc, fd, map);
	if (!values)
	{
		free(fc);
		free(str);
		handle_invalid_color(fd, map, "Error\nInvalid Rgb value\n");
	}
    if (values[0] < 0 || values[0] > 255
     || values[1] < 0 || values[1] > 255
     || values[2] < 0 || values[2] > 255)
    {
        free(values);
        free(fc);
        free(str);
        handle_invalid_color(fd, map, "Error\nRGB value out of range\n");
    }
    *target = values;
    free(fc);
}

