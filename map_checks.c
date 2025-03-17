/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariel <mariel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:33:29 by santiago          #+#    #+#             */
/*   Updated: 2025/03/16 20:07:31 by mariel           ###   ########.fr       */
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
		while (world[i][j])
		{
			//printf("analizing char [%d]: %c\n", j, world[i][j]);
			if (!my_strchr("01NSEW ", world[i][j]))
				return (0);
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

int	valid_first_last_line(char **world, int lines)
{
	int	j;

	j = 0;
	while (world[0][j])
	{
		if (world[0][j] != '1' && world[0][j] != ' ')
		{
			printf("Error: First line incorrect\n");
			return (0);
		}
		j++;
	}
	j = 0;
	while (world[lines][j])
	{
		if (world[lines][j] != '1' && world[0][j] != ' ')
		{
			printf("Error: First line incorrect\n");
			return (0);
		}
		j++;
	}
	printf("Ciao esco correttamente da valid first and last line\n");
	return (1);
}

void	get_line_data(t_analisys *line, char *str)
{
	int	i;

	i = 0;
	line->end = -1;
	line->start = -1;
	line->len = 0;
	while (str[i])
	{
		while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (line->start == -1)
			line->start = i;
		while (ft_strchr("01NSEW", str[i]) || str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		{
			if (str[i] == '1' || str[i] == '0') 
				line->end = i;
			i++;
		}
		i++;
	}
	line->len = line->end - line->start;
}

int	check_line1(char **world, t_analisys *line, t_analisys *prev_line, int i)
{
	printf("Ciao sono dentro check line 1\n");
	while (line->start < prev_line->start)
	{
		if (world[i][line->start] != '1')
		{
			printf("Error: Line %d not closed\n", i);
			return (0);
		}
		line->start++;
	}
	while (line->start > prev_line->start)
	{
		if (world[i][line->start] != '1')
		{
			printf("Error: Line %d not closed\n", i);
			return (0);
		} 
		if (world[i - 1][prev_line->start] != '1')
		{
			printf("Error: Line %d not closed\n", i);
			return (0);
		}
		prev_line->start++;
	}
	return (1);
}

int	map_closed(char **world)
{
	printf("Ciao sono dentro map closed\n");
	int			i;
	t_analisys	line;
	t_analisys	prev_line;

	i = 1;
	while (world[i + 1])
	{
		get_line_data(&line, world[i]);
		get_line_data(&prev_line, world[i - 1]);
		printf("Analazing line %s\n", world[i]);
		printf("prev line: %s\n", world[i - 1]);
		printf("PREV START: %d\tPREV END: %d\nLINE START: %d\tLINE END: %d\n", prev_line.start, prev_line.end, line.start, line.end);
		if (line.start == prev_line.start && line.end == prev_line.end)
		{
			if (world[i][line.start] != '1' || world[i][line.end] != '1')
				printf("Errore: map not closed at line");
			return (0);
		}
		if (line.start != prev_line.start)
		{
			if (!check_line1(world, &line, &prev_line, i))
					return (0);
		}
		i++;
	}
	printf("Ciao esco correttamente da map closed\n");
	return (1);
}

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
    if (!map_valid_char(world) || !valid_first_last_line(world, lines - 1) || !map_closed(world))	
		print_error("Error: Invalid map\n");
	return (1);
}