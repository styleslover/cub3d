/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:39:16 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/27 18:27:26 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_empty_lines(char **world)
{
	int	i;
	int	empty_line_found;

	i = 0;
	empty_line_found = 0;
	while (world[i])
	{
		if (is_empty_line(world[i]))
			empty_line_found = 1;
		else if (empty_line_found)
			return (0);
		i++;
	}
	return (1);
}

void	check_player_number(int player, t_map_data *map)
{
	if (player != 1)
		handle_map_error(NULL, -1, map,
			"Error\nThere must be exactly one player start\n");
}

int	map_valid_char(char **world, t_map_data *map)
{
	int	i;
	int	player;
	int	j;

	i = 0;
	player = 0;
	while (world[i])
	{
		j = 0;
		while (world[i][j] == ' ' && world[i][j] <= '\r')
			j++;
		while (world[i][j])
		{
			if (!my_strchr("01NSEW ", world[i][j]))
				handle_map_error(NULL, -1, map,
					"Error\nInvalid character in map\n");
			if (my_strchr("NSEW", world[i][j]))
				player++;
			j++;
		}
		i++;
	}
	check_player_number(player, map);
	return (1);
}

void	get_line_data(t_line *line, char *str)
{
	int	i;

	i = 0;
	line->end = 0;
	line->start = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	line->start = i;
	while (str[i])
	{
		if (ft_strchr("01NSEW", str[i]))
			line->end = i;
		i++;
	}
}
