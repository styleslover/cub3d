/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:39:22 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/26 20:16:46 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_cardinals(char **world, int i, int j)
{
	if (i == 0 || j == 0 || !world[i + 1] || !world[i - 1])
		return (0);
	if (ft_strlen(world[i]) <= j + 1 || j >= ft_strlen(world[i - 1])
		|| j >= ft_strlen(world[i + 1]) || j - 1 < 0)
		return (0);
	if (my_strchr("0NSEW", world[i][j]))
	{
		if (my_strchr("01NSEW", world[i + 1][j])
			&& my_strchr("01NSEW", world[i - 1][j])
			&& my_strchr("01NSEW", world[i][j + 1])
			&& my_strchr("01NSEW", world[i][j - 1]))
			return (1);
	}
	return (0);
}

int	is_map_closed(char **world, t_line *line)
{
	int		i;
	int		j;

	i = 0;
	while (world[i])
	{
		get_line_data(line, world[i]);
		j = line->start;
		while (j <= line->end)
		{
			if (my_strchr("0NSEW", world[i][j]))
			{
				if (i == 0 || j == 0 || !world[i + 1] || !world[i][j + 1])
					return (0);
				if (!check_cardinals(world, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map(char **world, t_map_data *map)
{
	t_line	line;

	if (!map_valid_char(world, map) || !is_map_closed(world, &line)
		|| !map_empty_lines(world))
	{
		handle_map_error(NULL, -1, map, "Error\nInvalid map\n");
	}
	return (1);
}
