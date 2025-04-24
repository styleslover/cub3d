/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 23:58:46 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/25 00:04:39 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_empty_line(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str != 32 && !(*str >= 9 && *str <= 13))
			return (0);
		str++;
	}
	return (1);
}

int	is_valid_config_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	return (ft_strncmp(str + i, "NO ", 3) == 0
		|| ft_strncmp(str + i, "SO ", 3) == 0
		|| ft_strncmp(str + i, "WE ", 3) == 0
		|| ft_strncmp(str + i, "EA ", 3) == 0
		|| ft_strncmp(str + i, "F ", 2) == 0
		|| ft_strncmp(str + i, "C ", 2) == 0);
}

void	check_empty_file(int current_line, t_map_data *map)
{
	if (!current_line)
	{
		printf("Error: empty file\n");
		free_map(map);
		exit(1);
	}
}

void	handle_config_error(int fd, t_map_data *map, char *message)
{
	close(fd);
	free_map(map);
	print_error(message);
	return ;
}

void	handle_config_line(char *line, t_map_data *map,
	int fd, int *config_done)
{
	if (is_map_line(line))
	{
		close(fd);
		printf("Error\nInvalid configuration line\n");
	}
	else
	{
		parse_config_line(line, map, fd);
		if (map->north_txtr && map->south_txtr && map->west_txtr
			&& map->east_txtr && map->floor_color && map->ceiling_color)
			*config_done = 1;
	}
}

int	skip_spaces_check_sign(char *str, int *i)
{
	while (str[*i] == 32 || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '+')
	{
		if (!ft_isdigit(str[*i + 1]))
			return (0);
		(*i)++;
	}
	if (str[*i] == '-')
	{
		printf("Negative value\n");
		return (0);
	}
	return (1);
}
