/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 23:52:21 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/26 17:40:00 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_fc_format(char *fc, int fd, t_map_data *map)
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
		close(fd);
		free(fc);
		free_map(map);
		print_error("Invalid rgb\n");
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

void	handle_invalid_color(int fd, t_map_data *map)
{
	close(fd);
	free_map(map);
	clear_gnl();
	print_error("Error: invalid color line\n");
}

void	parse_floor_ceiling(int i, char *str, t_map_data *map, int fd)
{
	char	*fc;
	int		**target;

	fc = 0;
	target = get_target_color(i, str, map);
	if (!target || !str[i + 2])
		return (handle_invalid_color(fd, map));
	fc = strcmp_from_i(i + 2, str);
	if (!fc)
		handle_config_error(fd, map, "Error: invalid color format\n");
	if (!check_fc_format(fc, fd, map))
		return ;
	*target = parse_rgb_values(fc);
	free(fc);
	if (!*target)
		handle_invalid_color(fd, map);
}

