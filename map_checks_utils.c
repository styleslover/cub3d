/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:39:16 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/24 19:39:53 by mabrigo          ###   ########.fr       */
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

int	map_valid_char(char **world, int i, int player)
{
	int	j;

	while (world[i])
	{
		j = 0;
		while (world[i][j] == 32 || (world[i][j] >= 9 && world[i][j] <= 13))
			j++;
		while (world[i][j])
		{
			if (world[i][j] == '\t')
			{
				printf("Error: tab is an invalid character!\n");
				return (0);
			}
			if (!my_strchr("01NSEW ", world[i][j]))
				return (0);
			if (my_strchr("NSEW", world[i][j]))
				player++;
			j++;
		}
		i++;
	}
	if (player != 1)
		return (printf("Error: there must be only one player!\n"), 0);
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