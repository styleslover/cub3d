/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:33:29 by santiago          #+#    #+#             */
/*   Updated: 2025/03/18 20:47:26 by mabrigo          ###   ########.fr       */
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
			if (!my_strchr("01NSEW ", world[i][j]))
			{
				return (0);
			}
			if (world[i][j] == 32)
				world[i][j] = '1';
			if (my_strchr("NSEW", world[i][j]))
			{
				if (j != 0 && world[i][j + 1])
					player++;
				else
					print_error("Error: Bad player position");
				printf("Player in line %d: %c\n", i, world[i][j]);
			}
			j++;
		}
		i++;
	}
	if (player != 1)
		print_error("Error: player must be one");
	printf("Ciao esco correttamente da map valid char\n");
	return (1);
}

void	flood_fill(char **world, int i, int j, int rows, int cols)
{
	if (i < 0 || j < 0 || i >= rows || j >= cols)
		return ;
	world[i][j] = 'X';
	flood_fill(world, i + 1, j, rows, cols);
	flood_fill(world, i - 1, j, rows, cols);
	flood_fill(world, i, j + 1, rows, cols);
	flood_fill(world, i, j - 1, rows, cols);
}

int	flood_fill_check(char **og_world)
{
	//todo
}

int	check_map(char **world)
{
	int	lines;
	int	cols;
	int	i;
	int	len;

	lines = 0;
	cols = 0;
	i = 0;
	while (world[i])
	{
		len = ft_strlen(world[i]);
		if (len > cols)
			cols = len;
		lines++;
		i++;
	}
	if	(!map_valid_char(world))
		print_error("Error: Invalid map\n");
	if (flood_fill_check(world))
        print_error("Error: Map is open to the outside\n");
	return (1);
}