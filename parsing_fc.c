/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 23:52:21 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/27 20:10:53 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_fc_format(char *fc)
{
	int	j;
	int	commas;

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
	if ((ft_strncmp(str + i, "F ", 2) == 0)
		|| (ft_strncmp(str + i, "F\t", 2) == 0))
	{
		if (map->floor_color)
		{
			free(map->floor_color);
			map->floor_color = NULL;
			return (NULL);
		}
		return (&map->floor_color);
	}
	else if ((ft_strncmp(str + i, "C ", 2) == 0)
		|| (ft_strncmp(str + i, "C\t", 2) == 0))
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
	printf("%s", message);
	exit(1);
}

int	*finalize_rgb_values(int fd, char *fc, char *str, t_map_data *map)
{
	int		*values;

	values = parse_rgb_values(fc);
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
	return (values);
}

void	parse_floor_ceiling(int i, char *str, t_map_data *map, int fd)
{
	char	*fc;
	int		**target;
	int		*values;

	target = get_target_color(i, str, map);
	fc = strcmp_from_i(i + 2, str);
	if (!target || !str[i + 2] || !fc || !check_fc_format(fc))
	{
		free(str);
		if (fc)
			free(fc);
		handle_invalid_color(fd, map, "Error\nInvalid color line\n");
	}
	values = finalize_rgb_values(fd, fc, str, map);
	*target = values;
	free(fc);
}
