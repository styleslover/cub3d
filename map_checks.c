/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santiago <santiago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:33:29 by santiago          #+#    #+#             */
/*   Updated: 2025/03/15 19:03:55 by santiago         ###   ########.fr       */
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
		//printf("analizing line [%d]: %s\n", i, world[i]);
		while (world[i][j])
		{
			//printf("analizing char [%d]: %c\n", j, world[i][j]);
			if (!my_strchr("01NSEW ", world[i][j]))
				return (0);
			if (my_strchr("NSEW", world[i][j]))
				player++;
			if (player > 1)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	valid_first_last_line(char **world, int lines)
{
	int	j;

	j = 0;
	while (world[0][j])
	{
		if (world[0][j] != '1')
			return (0);
		j++;
	}
	j = 0;
	while (world[lines][j])
	{
		if (world[lines][j] != '1')
			return (0);
		j++;
	}
	return (1);
}
/*
int	map_closed(char **world)
{
	int	i;
	int	j;
	int	line_len;
	int	prev_line_len;
	int	start_lin

	i = 0;
	line_len = 0;
	prev_line_len = 0;
	while (world[i])
	{
		line_len = ft_strlen(world[i]);
		j = 0;
		find
		while (world[i][j])
		{
			if (i != 0 && line_len > prev_line_len)
				return (0);
		}
		i++;
	}
}
*/
int	check_map(char **world)
{
	int	lines;
	int	i;
	
	lines = 0;
	i = 0;
	while (world[i])
	{
		lines++;
		i++;
	}
    if (!map_valid_char(world) || !valid_first_last_line(world, lines - 1))	
		print_error("Error: Invalid map\n");
	return (1);
}