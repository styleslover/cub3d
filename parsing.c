/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 22:52:55 by mariel            #+#    #+#             */
/*   Updated: 2025/04/09 18:27:10 by mabrigo          ###   ########.fr       */
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

	i = 0;
	digit_found = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			digit_found = 1;
			i++;
		}
		else if (str[i] == ' ' || str[i] == '\t')
		{
			i++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
		}
	}
	if (str[i] != '\0')
		return (0);
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
		if (!trimmed)
		{
			free_matrix(splitted);
			free(rgb_values);
			return (0);
		}
		if (!check_single_value(trimmed))
		{
			free(trimmed);
			free_matrix(splitted);
			free(rgb_values);
			printf("Error: something's wrong in color values\n");
			return (0);
		}
		rgb_values[i] = ft_atoi(trimmed);
		if (rgb_values[i] < 0 || rgb_values[i] > 255)
		{
			free(trimmed);
			free_matrix(splitted);
			free(rgb_values);
			return (0);
		}
		free(trimmed);
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
		free(*txtr);
		*txtr = NULL;
		print_error(err_msg);
	}
	*txtr = value;
}

void parse_floor_ceiling(int i, char *str, t_map_data *map)
{
    char *fc = strcmp_from_i(i + 2, str);
    if (!fc)
    {
        print_error("Error: invalid color format\n");
        return;
    }

    int **target = NULL;
    if (ft_strncmp(str + i, "F ", 2) == 0)
        target = &map->floor_color;
    else if (ft_strncmp(str + i, "C ", 2) == 0)
        target = &map->ceiling_color;

    if (!target)
    {
        free(fc);  // Libera la stringa allocata
        print_error("Error: invalid color line\n");
        return;
    }

    if (*target)
    {
        free(*target);
        *target = NULL;
        free(fc);  // Libera la stringa allocata
        print_error("Error: double configuration\n");
        return;
    }

    *target = parse_rgb_values(fc);
    free(fc);  // Libera la stringa allocata dopo l'uso
    
    if (!*target)
        print_error("Error: invalid color values\n");
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

void parse_config_line(char *str, t_map_data *map)
{
    int i = 0;
    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;

    if (!is_valid_config_line(str))
    {
        printf("Error: invalid configuration line: '%s'\n", str);
        exit(1);
    }

    char *value = strcmp_from_i(i + (str[i+1] == ' ' ? 3 : 2), str);
    if (!value)
    {
        printf("Error: invalid texture path\n");
        exit(1);
    }

    // Gestione più sicura delle texture
    char **target_texture = NULL;
    if (!ft_strncmp(str + i, "NO ", 3))
        target_texture = &map->north_txtr;
    else if (!ft_strncmp(str + i, "SO ", 3))
        target_texture = &map->south_txtr;
    else if (!ft_strncmp(str + i, "WE ", 3))
        target_texture = &map->west_txtr;
    else if (!ft_strncmp(str + i, "EA ", 3))
        target_texture = &map->east_txtr;

    if (target_texture)
    {
        if (*target_texture)
            free(*target_texture);
        *target_texture = value;
    }
    else if (!ft_strncmp(str + i, "F ", 2) || !ft_strncmp(str + i, "C ", 2))
    {
        free(value);  // Libera la stringa poiché parse_floor_ceiling ne crea una nuova
        parse_floor_ceiling(i, str, map);
    }
    else
    {
        free(value);  // Libera la stringa se non è stata usata
        printf("Error: unknown configuration line: '%s'\n", str + i);
        exit(1);
    }
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
		{
			free(line);
			free_matrix(map);
			return (NULL);
		}
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
				exit(1);
			}	
		}
		else
		{
			if (is_map_line(line))
			{
				free(line);
				exit(1);
			}
			else
			{
				parse_config_line(line, map);
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
		printf("Error: empty file\n");
		return ;
	}
	map->world = load_map(av[1], &map_start_line);
	if (!check_map(map->world))
	{
		free_map(map);
		printf("Error: Failed to load map\n");
		exit(1);
	}
	map->map_width = ft_strlen(map->world[0]);  // Larghezza della mappa
    map->map_height = 0;
    while (map->world[map->map_height] != NULL)
        map->map_height++;
}
