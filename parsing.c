/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 22:52:55 by mariel            #+#    #+#             */
/*   Updated: 2025/04/24 22:19:32 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_empty_line(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str != 32 && !(*str >= 9 && *str <= 13))
			return (0);
		str++;
	}
	return (1);
}

int	skip_spaces_check_sign(char *str, int *i)
{
	while (str[*i] == 32 || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '+')
	{
		if (!ft_isdigit(str[*i + 1]))
			return (0);
		(*i)++;
	}
	if (str[*i] == '-')
	{
		printf("Negative value\n");
		return (0);
	}
	return (1);
}

int	process_digit_and_spaces(char *str, int *i, int *digit_found, int *in_number)
{
	if (ft_isdigit(str[*i]))
	{
		if (*in_number == 2)
			return (0);
		*digit_found = 1;
		*in_number = 1;
		(*i)++;
	}
	else if ((str[*i] == ' ' || str[*i] == '\t') && *in_number == 1)
	{
		*in_number = 2;
		while (str[*i] == ' ' || str[*i] == '\t')
			(*i)++;
	}
	else if (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	else
	{
		printf("Error: invalid character in RGB value\n");
		return (0);
	}
	return (1);
}

int	check_single_value(char *str)
{
	int i;
	int digit_found;
	int in_number;

	i = 0;
	digit_found = 0;
	in_number = 0;
	if (!skip_spaces_check_sign(str, &i))
		return (0);
	while (str[i])
	{
		if (!process_digit_and_spaces(str, &i, &digit_found, &in_number))
			return (0);
	}
	return (digit_found);
}

int rgb_char_to_int(int *rgb_values, char **input)
{
    int i;
    char *trimmed;

    i = 0;
    while (i < 3 && input[i])
    {
        trimmed = ft_strtrim(input[i], " \t\n\r");
        if (!trimmed || !check_single_value(trimmed))
        {
            printf("Error here\n");
            if (trimmed)
                free(trimmed);
            return (0);
        }
        rgb_values[i] = ft_atoi(trimmed);
        free(trimmed);
        if (rgb_values[i] < 0 || rgb_values[i] > 255)
        {
            print_error("Error: RGB values must be between 0 and 255\n");
            return (0);
        }
        i++;
    }
    return (1);
}
int	count_check_rgb_values(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
		i++;
	if (i != 3)
	{
		free_matrix(splitted);
		return (1);
	}
	return (0);
}

int *parse_rgb_values(char *str)
{
    char **splitted;
    int *rgb_values;

    splitted = ft_split(str, ',');
    if (!splitted)
	{
		return (0);
	}
	if (count_check_rgb_values(splitted))
		return (0);
    rgb_values = (int *)malloc(sizeof(int) * 3);
    if (!rgb_values)
    {
        free_matrix(splitted);
        return (0);
    }
    if (!rgb_char_to_int(rgb_values, splitted))
    {
        free_matrix(splitted);
        free(rgb_values);
        return (0);
    }
    free_matrix(splitted);
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

void handle_config_error(int fd, t_map_data *map, char *message)
{
    close(fd);
    free_map(map);
    print_error(message);
	//printf("cacchio\n");
	return ;
    //exit(1);
}

int check_fc_format(char *fc, int fd, t_map_data *map)
{
    int j;
    int commas;
    
    j = 0;
    commas = 0;
    while (fc[j])
    {
        if (fc[j] == ',')
            commas++;
        j++;
    }
    if (commas != 2)
    {
        close(fd);
        free(fc);
        free_map(map);
        print_error("Invalid rgb\n");
        return (0);
    }
    return (1);
}

int **get_target_color(int i, char *str, t_map_data *map)
{
    if (ft_strncmp(str + i, "F ", 2) == 0)
    {
        if (map->floor_color)
        {
            free(map->floor_color);
            map->floor_color = NULL;
            print_error("Error\nDouble floor configuration\n");
            return (NULL);
        }
        return (&map->floor_color);
    }
    else if (ft_strncmp(str + i, "C ", 2) == 0)
    {
        if (map->ceiling_color)
        {
            free(map->ceiling_color);
            map->ceiling_color = NULL;
            print_error("Error\nDouble ceiling configuration\n");
            return (NULL);
        }
        return (&map->ceiling_color);
    }
    return (NULL);
}

void handle_invalid_color(int fd, t_map_data *map)
{
    close(fd);
    free_map(map);
    print_error("Error: invalid color line\n");
}

void parse_floor_ceiling(int i, char *str, t_map_data *map, int fd)
{
    char *fc;
    int **target;

    fc = 0;
    target = get_target_color(i, str, map);
    if (!target || !str[i + 2])
        return handle_invalid_color(fd, map);
    if (*target)
        handle_config_error(fd, map, "Error: double configuration\n");
    fc = strcmp_from_i(i + 2, str);
    if (!fc)
        handle_config_error(fd, map, "Error: invalid color format\n");
    if (!check_fc_format(fc, fd, map))
        return;
    *target = parse_rgb_values(fc);
    free(fc);
    if (!*target)
        handle_invalid_color(fd, map);
}

int is_valid_config_line(char *str)
{
    int i = 0;
    
    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
	{
        i++;
	}
    return (ft_strncmp(str + i, "NO ", 3) == 0 ||
           ft_strncmp(str + i, "SO ", 3) == 0 ||
           ft_strncmp(str + i, "WE ", 3) == 0 ||
           ft_strncmp(str + i, "EA ", 3) == 0 ||
           ft_strncmp(str + i, "F ", 2) == 0 ||
           ft_strncmp(str + i, "C ", 2) == 0);
}

int	is_valid_texture_path(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

void handle_texture(t_map_data *map, int fd, char *str, int offset)
{
    char *path;
	
	path = strcmp_from_i(offset, str);
    if (!path)
	{
		//free(path);
        handle_config_error(fd, map, "Error: Invalid texture path format\n");
		return;
    }
    if (!is_valid_texture_path(path))
    {
		free(path);
		handle_config_error(fd, map, "Error\nInvalid texture path\n");
		return ;
    }
    if (!ft_strncmp(str, "NO ", 3))
        assign_texture(&map->north_txtr, path, "Error\nNO texture\n");
    else if (!ft_strncmp(str, "SO ", 3))
        assign_texture(&map->south_txtr, path, "Error\nSO texture\n");
    else if (!ft_strncmp(str, "WE ", 3))
        assign_texture(&map->west_txtr, path, "Error\nWE texture\n");
    else
        assign_texture(&map->east_txtr, path, "Error\nEA texture\n");
}

void parse_config_line(char *str, t_map_data *map, int fd)
{
    int i = 0;

    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (!is_valid_config_line(str))
    {
        handle_config_error(fd, map, "Error: invalid configuration line\n");
        return;
    }
    
    if (!ft_strncmp(str + i, "NO ", 3) || !ft_strncmp(str + i, "SO ", 3))
        handle_texture(map, fd, str + i, i + 3);
    else if (!ft_strncmp(str + i, "WE ", 3) || !ft_strncmp(str + i, "EA ", 3))
        handle_texture(map, fd, str + i, i + 3);
    else if (!ft_strncmp(str + i, "F ", 2) || !ft_strncmp(str + i, "C ", 2))
        parse_floor_ceiling(i, str, map, fd);
    else
        handle_config_error(fd, map, "Error: Unknown configuration directive\n");
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
char **set_map(int map_start_line, char *av, int *fd)
{
    int     lines;
    char    **map;

    *fd = open(av, O_RDONLY);
    if (*fd < 0)
        return NULL;

    lines = count_lines(av, *fd);
    if (lines <= 0)
    {
        close(*fd);
        return NULL;
    }
    map = malloc((lines - map_start_line + 1) * sizeof(char *));
    if (!map)
    {
        close(*fd);
        return NULL;
    }
    return map;
}

int get_map(char **map, int fd, int map_start_line)
{
    char    *line;
    int     i;

    i = 0;
    while (i < map_start_line)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        free(line);
        i++;
    }
    i = 0;
    while ((line = get_next_line(fd)))
    {
        if (is_map_line(line) || is_empty_line(line))
        {
            map[i] = trim_newline(line);
            i++;
        }
        else
            free(line);
    }
    map[i] = NULL;
    return i;
}

char **load_map(char *av, int map_start_line)
{
    int     fd;
    char    **map;

    map = set_map(map_start_line, av, &fd);
    if (!map)
        return NULL;

    if (get_map(map, fd, map_start_line) == 0)
    {
        free(map);
        close(fd);
        return NULL;
    }
    close(fd);
    return map;
}

// Gestisce una riga della configurazione durante il parsing
void handle_config_line(char *line, t_map_data *map, int fd, int *config_done)
{
	if (is_map_line(line))
	{
		close(fd);
		printf("Error\nInvalid configuration line\n");
	}
	else
	{
		parse_config_line(line, map, fd);
		if (map->north_txtr && map->south_txtr && map->west_txtr
			&& map->east_txtr && map->floor_color && map->ceiling_color)
			*config_done = 1;
	}
}

// Gestisce una riga dopo che la configurazione è completata
int handle_map_line(char *line, int current_line, int *map_start_line)
{
	if (is_map_line(line) != 0)
	{
		if (*map_start_line == 0)
			*map_start_line = current_line - 1;
		return (1);
	}
	return (0);
}

// Gestisce un errore nella mappa e pulisce le risorse
void handle_map_error(char *line, int fd, t_map_data *map)
{
	free(line);
	close(fd);
	free_map(map);
	printf("Error\ninvalid map line\n");
	clear_gnl();
	exit(1);
}

// Calcola le dimensioni della mappa
void calculate_map_dimensions(t_map_data *map)
{
	while (map->world[map->map_height])
	{
		if (ft_strlen(map->world[map->map_height]) > map->map_width)
			map->map_width = ft_strlen(map->world[map->map_height]);
		map->map_height++;
	}
}

// Verifica se il file è vuoto
void check_empty_file(int current_line, t_map_data *map)
{
    if (!current_line)
    {
        printf("Error: empty file\n");
        free_map(map);
        exit(1);  // Add this line to exit the program
    }
}

// Carica e verifica la mappa
void load_and_check_map(char **av, t_map_data *map, int map_start_line)
{
    map->world = load_map(av[1], map_start_line);
    if (!map->world)
    {
        printf("Error: Failed to load map\n");
        free_map(map);
        exit(1);
    }
    if (!check_map(map->world))
    {
        printf("Error: Invalid map\n");
        free_map(map);
        exit(1);
    }
    calculate_map_dimensions(map);
}

// Processa una riga durante il parsing del file
void process_line(char *line, t_map_data *map, int fd, int *config_done,
				int *map_start_line, int *current_line)
{
	(*current_line)++;
	if (is_empty_line(line))
	{
		free(line);
		return;
	}
	if (*config_done)
	{
		if (!handle_map_line(line, *current_line, map_start_line))
			handle_map_error(line, fd, map);
	}
	else
		handle_config_line(line, map, fd, config_done);
	free(line);
}

// Funzione principale di parsing del file
void parse_file(char **av, int fd, t_map_data *map)
{
	char	*line;
	int		config_done;
	int		map_start_line;
	int		current_line;

	config_done = 0;
	map_start_line = 0;
	current_line = 0;
	init_map(map);
	while ((line = get_next_line(fd)))
		process_line(line, map, fd, &config_done, &map_start_line, &current_line);
	close(fd);
	check_empty_file(current_line, map);
	load_and_check_map(av, map, map_start_line);
}
