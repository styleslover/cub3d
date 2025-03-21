/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: santiago <santiago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:33:29 by santiago          #+#    #+#             */
/*   Updated: 2025/03/15 19:03:55 by santiago         ###   ########.fr       */
=======
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:39:22 by mabrigo           #+#    #+#             */
/*   Updated: 2025/03/20 20:15:55 by mabrigo          ###   ########.fr       */
>>>>>>> main
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
<<<<<<< HEAD
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
=======
		while (world[i][j] == 32 || (world[i][j] >= 9 && world[i][j] <= 13))
			j++;
		while (world[i][j])
		{
			if (!my_strchr("01NSEW \t", world[i][j]))
				return (0);
			if (my_strchr("NSEW", world[i][j]))
				player++;
>>>>>>> main
			j++;
		}
		i++;
	}
<<<<<<< HEAD
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
=======
	if (player != 1)
		return (0);
	printf("Ciao esco correttamente da map valid char\n");
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

    if (!map_valid_char(world) || !is_map_closed(world, &line))
	{
		printf("Error: Invalid map\n");
		return (0);
	}
>>>>>>> main
	return (1);
}