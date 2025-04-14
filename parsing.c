/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 22:52:55 by mariel            #+#    #+#             */
/*   Updated: 2025/04/14 12:31:02 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_empty_line(char *str)
{
	if (!str)
		return (1);  // Linea nulla è considerata vuota

	while (*str)
	{
		if (*str != 32 && !(*str >= 9 && *str <= 13))
			return (0);  // La linea non è vuota
		str++;
	}
	return (1);  // La linea è vuota
}

int	check_single_value(char *str)
{
    int i;
    int digit_found;
    int in_number;

    i = 0;
    digit_found = 0;
    in_number = 0;
    
    // Salta spazi iniziali
    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
    
    // Gestisci segno opzionale
    if (str[i] == '+')
	{
		if (!ft_isdigit(str[i + 1]))
			return (0);
        i++;
	}
    if (str[i] == '-')
	{
		return (0);
	}
    while (str[i])
    {
        if (ft_isdigit(str[i]))
        {
            if (in_number == 2) // Se abbiamo già lasciato il numero (spazi dopo cifre)
                return (0);     // Non accettiamo altre cifre
            digit_found = 1;
            in_number = 1;      // Siamo dentro un numero
            i++;
        }
        else if (str[i] == ' ' || str[i] == '\t')
        {
            if (in_number == 1) // Se abbiamo appena finito un numero
                in_number = 2;   // Segnala che siamo dopo il numero
            i++;
            while (str[i] == ' ' || str[i] == '\t')
                i++;
        }
        else
        {
            return (0); // Carattere non valido
        }
    }
    return (digit_found);
}

int	*parse_rgb_values(char *str)
{
	char	**splitted;
	int		*rgb_values;
	char	*trimmed;
	int		i;

	splitted = ft_split(str, ',');
	if (!splitted)
		return (0);
	i = 0;
	while (splitted[i])
		i++;
	if (i != 3)
	{
		free_matrix(splitted);
		return (NULL);
	}
	rgb_values = (int *)malloc(sizeof(int) * 3);
	if (!rgb_values)
	{
		free_matrix(splitted);
		return (0);
	}
	i = 0;
	while (i < 3 && splitted[i])
	{
		trimmed = ft_strtrim(splitted[i], " \t\n\r");
		if (!trimmed || !check_single_value(trimmed))
		{
			if (trimmed)
				free(trimmed);
			free_matrix(splitted);
			free(rgb_values);
			printf("Error: something's wrong in color values\n");
			return (0);
		}
		rgb_values[i] = ft_atoi(trimmed);
		free(trimmed);
		if (rgb_values[i] < 0 || rgb_values[i] > 255)
		{
			//debug
			printf("errore in ceiling o floor\n");
			free_matrix(splitted);
			free(rgb_values);
			return (0);
		}
		i++;
	}
	free_matrix(splitted);
	if (i != 3)
	{
		free(rgb_values);
		return (NULL);
	}
	return (rgb_values);
}

void	assign_texture(char **txtr, char *value, char *err_msg)
{
	if (*txtr)
	{
		free(value);
		free(*txtr);
		*txtr = NULL;
		print_error(err_msg);
	}
	else
		*txtr = value;
}

void	parse_floor_ceiling(int i, char *str, t_map_data *map, int fd)
{
	char	*fc;
	int		**target;

	fc = 0;
	target = 0;
	if (ft_strncmp(str + i, "F ", 2) == 0)
	{
		if (map->floor_color)
		{
			free(map->floor_color);
			map->floor_color = NULL;
			print_error("Error\n");
		}
		else
			target = &map->floor_color;
	}
	else if (ft_strncmp(str + i, "C ", 2) == 0)
	{
		if (map->ceiling_color)
			{
				free(map->ceiling_color);
				map->ceiling_color = NULL;
				print_error("Error\n");
			}
			else
				target = &map->ceiling_color;
	}
	if (!target || !str[i + 2])
	{
		close(fd);
		free_map(map);
		free(target);
		print_error("Error: invalid color line\n");
		//exit (1);
		return ;
	}
	if (*target)
	{
		close(fd);
		free_map(map);
		print_error("Error: double configuration\n");
		exit(1);
	}
	fc = strcmp_from_i(i + 2, str);
	if (!fc)
	{
		close(fd);
		free_map(map);
		print_error("Error: invalid color format\n");
		exit(1);
	}
	*target = parse_rgb_values(fc);
	free(fc);
	if (!*target)
	{
		close(fd);
		free_map(map);
		print_error("Error: invalid color values\n");
		//exit(1); //QUESTO QUA DA 2 ERRORI SE COMMENTATO MA TOGLIE I STILL REACHABLE
	}
}

int is_valid_config_line(char *str)
{
    int i = 0;
    
    // Salta spazi iniziali
    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
		
    // Verifica se è una configurazione valida
    return (ft_strncmp(str + i, "NO ", 3) == 0 ||
           ft_strncmp(str + i, "SO ", 3) == 0 ||
           ft_strncmp(str + i, "WE ", 3) == 0 ||
           ft_strncmp(str + i, "EA ", 3) == 0 ||
           ft_strncmp(str + i, "F ", 2) == 0 ||
           ft_strncmp(str + i, "C ", 2) == 0);
}

void	parse_config_line(char *str, t_map_data *map, int fd)
{
	int		i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (!is_valid_config_line(str))
	{
		close(fd);
		printf("Error: invalid configuration line\n");
		free_map(map);
		exit(1);
	}
	if (!ft_strncmp(str + i, "NO ", 3))
		assign_texture(&map->north_txtr, strcmp_from_i(i + 3, str),
			"Error: NO texture\n");
	else if (!ft_strncmp(str + i, "SO ", 3))
		assign_texture(&map->south_txtr, strcmp_from_i(i + 3, str),
			"Error: SO texture\n");
	else if (!ft_strncmp(str + i, "WE ", 3))
		assign_texture(&map->west_txtr, strcmp_from_i(i + 3, str),
			"Error: WE texture\n");
	else if (!ft_strncmp(str + i, "EA ", 3))
		assign_texture(&map->east_txtr, strcmp_from_i(i + 3, str),
			"Error: EA texture\n");
	else if (!ft_strncmp(str + i, "F ", 2) || !ft_strncmp(str + i, "C ", 2))
		parse_floor_ceiling(i, str, map, fd);
}

int	is_map_line(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'))
		i++;
	if (!str[i])
		return (0);
	if (str[i] == '1' || str[i] == '0' || str[i] == 'N'
		|| str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
	{
		if (!ft_strncmp(&str[i], "NO ", 3) || !ft_strncmp(&str[i], "SO ", 3)
			|| !ft_strncmp(&str[i], "WE ", 3) || !ft_strncmp(&str[i], "EA ", 3)
			|| !ft_strncmp(&str[i], "F ", 2) || !ft_strncmp(&str[i], "C ", 2))
			return (0);
		return (1);
	}
	return (0);
}

char	**load_map(char *av, int *map_start_line)
{
	int		fd;
	int		i;
	int		lines;
	char	**map;
	char	*line;

	fd = open(av, O_RDONLY);
    if (fd < 0)
		return (0);
	lines = count_lines(av, fd);
	if (lines <= 0)
	{
		close(fd);
		return (NULL);
	}
	map = malloc((lines - *map_start_line + 1) * sizeof(char *));  // +1 per NULL finale
	if (!map)
	{
		close(fd);
		return (NULL);
	}
	fd = open(av, O_RDONLY);
	if (fd < 0)
	{
		free(map);
		return (NULL);
	}
	i = 0;
	while (i < *map_start_line)
	{
		line = get_next_line(fd);
		if (!line)  // Se get_next_line fallisce
			break;
		free(line);
		i++;
	}
	i = 0;
	while ((line = get_next_line(fd)))
	{
		if (is_map_line(line) || is_empty_line(line))
		{
			map[i] = line;
			map[i] = trim_newline(map[i]);
			i++;
		}
		else
			free(line);
	}
	map[i] = NULL;  // Terminatore NULL per l'array di stringhe
	close(fd);
	return (map);
}

void	parse_file(char **av, int fd, t_map_data *map)
{
	char	*line;
	int		line_len;
	int		config_done;
	int		map_start_line;
	int		current_line;

	init_map(map);
	line_len = 0;
	config_done = 0;
	map_start_line = 0;
	current_line = 0;
	while ((line = get_next_line(fd)))
	{
		current_line++;
		if (is_empty_line(line))
		{
			//printf("empty valid line\n");
			free(line);
			continue;
		}
		if (config_done)
		{
			if (is_map_line(line) != 0)
			{
				line_len = ft_strlen(line);
				if (line_len > map->win_width)
					map->win_width = line_len;
				map->win_height++;
				if (map_start_line == 0)
					map_start_line = current_line - 1;
			}
			else
			{
				free(line);
				close (fd);
				free_map(map);
				printf("Error: invalid map line\n");
				exit(1);
			}
		}
		else
		{
			if (is_map_line(line))
			{
				//free(line);
				close(fd);
				//free_map(map);
				printf("Error: Invalid configuration line\n");
				//exit(1);
			}
			else
			{
				parse_config_line(line, map, fd);
				if (map->north_txtr && map->south_txtr && map->west_txtr
					&& map->east_txtr && map->floor_color && map->ceiling_color)
				{
					config_done = 1;
				}
			}
		}
		free(line);
	}
	close(fd);
	if (!current_line)
	{
		//debug
		printf("Error: empty file\n");
		free_map(map);
		return ;
	}
	map->world = load_map(av[1], &map_start_line);
	if (!check_map(map->world))
	{
		printf("Error: Failed to load map\n");
		free_map(map);
		exit(1);
	}
    while (map->world[map->map_height])
	{
		if (ft_strlen(map->world[map->map_height]) > map->map_width)
			map->map_width = ft_strlen(map->world[map->map_height]);
        map->map_height++;
	}
}