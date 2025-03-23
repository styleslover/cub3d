/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:39:22 by mabrigo           #+#    #+#             */
/*   Updated: 2025/03/23 16:25:46 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	my_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return (1);
		s++;
	}
	return (0);
}

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

int	map_valid_char(char **world)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (world[i])
	{
		j = 0;
		while (world[i][j] == 32 || (world[i][j] >= 9 && world[i][j] <= 13))
			j++;
		while (world[i][j])
		{
			if (!my_strchr("01NSEW \t", world[i][j]))
				return (0);
			if (my_strchr("NSEW", world[i][j]))
				player++;
			j++;
		}
		i++;
	}
	if (player != 1)
		return (0);
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

int	check_cardinals(char **world, int i, int j)
{
	if (i == 0 || j == 0 || !world[i + 1] || !world[i][j + 1])
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

int	check_map(char **world)
{
	t_line	line;

    if (!map_valid_char(world) || !is_map_closed(world, &line)
		|| !map_empty_lines(world))
	{
		printf("Error: Invalid map\n");
		return (0);
	}
	return (1);
}