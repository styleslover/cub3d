/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 22:52:55 by mariel            #+#    #+#             */
/*   Updated: 2025/04/14 20:47:04 by damoncad         ###   ########.fr       */
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

int	check_single_value(char *str)
{
    int i;
    int digit_found;
    int in_number;

    i = 0;
    digit_found = 0;
    in_number = 0;
    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '+')
	{
		if (!ft_isdigit(str[i + 1]))
			return (0);
        i++;
	}
    if (str[i] == '-')
		return (0);
    while (str[i])
    {
        if (ft_isdigit(str[i]))
        {
            if (in_number == 2)
                return (0);
            digit_found = 1;
            in_number = 1;
            i++;
        }
        else if (str[i] == ' ' || str[i] == '\t')
        {
            if (in_number == 1)
                in_number = 2;
            i++;
            while (str[i] == ' ' || str[i] == '\t')
                i++;
        }
        else
		{
			printf("Error: invalid character in RGB value\n");
            return (0);
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
			return (0);
		}
		rgb_values[i] = ft_atoi(trimmed);
		free(trimmed);
		if (rgb_values[i] < 0 || rgb_values[i] > 255)
		{
			print_error("Error: RGB values must be between 0 and 255\n");
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
	int		j;
	int		commas;

	fc = 0;
	target = 0;
	j = 0;
	commas = 0;
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
		return ;
	}
	*target = parse_rgb_values(fc);
	free(fc);
	if (!*target)
	{
		close(fd);
		free_map(map);
		print_error("Error: invalid color values\n");
	}
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
	{
		printf("Error: invalid texture path\n");
		return (0);
	}
	close(fd);
	return (1);
}

void parse_config_line(char *str, t_map_data *map, int fd)
{
    int i = 0;

    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (!is_valid_config_line(str))
    {
        close(fd);
        printf("Error: invalid configuration line\n");
        free_map(map);
        return;
    }
    if (!ft_strncmp(str + i, "NO ", 3))
    {
        char *path = strcmp_from_i(i + 3, str);
        if (!is_valid_texture_path(path))
        {
            close(fd);
            printf("Error: Invalid path for NO texture\n");
			free(path);
            free_map(map);
            return;
        }
        assign_texture(&map->north_txtr, path, "Error: NO texture\n");
    }
    else if (!ft_strncmp(str + i, "SO ", 3))
    {
        char *path = strcmp_from_i(i + 3, str);
        if (!is_valid_texture_path(path))
        {
            close(fd);
            printf("Error: Invalid path for SO texture\n");
			free(path);
            free_map(map);
            return;
        }
        assign_texture(&map->south_txtr, path, "Error: SO texture\n");
    }
    else if (!ft_strncmp(str + i, "WE ", 3))
    {
        char *path = strcmp_from_i(i + 3, str);
        if (!is_valid_texture_path(path))
        {
            close(fd);
            printf("Error: Invalid path for WE texture\n");
			free(path);
            free_map(map);
            return;
        }
        assign_texture(&map->west_txtr, path, "Error: WE texture\n");
    }
    else if (!ft_strncmp(str + i, "EA ", 3))
    {
        char *path = strcmp_from_i(i + 3, str);
        if (!is_valid_texture_path(path))
        {
            close(fd);
            printf("Error: Invalid path for EA texture\n");
			free(path);
            free_map(map);
            return;
        }
        assign_texture(&map->east_txtr, path, "Error: EA texture\n");
    }
    else if (!ft_strncmp(str + i, "F ", 2) || !ft_strncmp(str + i, "C ", 2))
    {
        parse_floor_ceiling(i, str, map, fd);
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
			map[i] = line;
			map[i] = trim_newline(map[i]);
			i++;
		}
		else
			free(line);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

void	parse_if_config_done(char *line, int *map_start_line, int current_line, t_map_data *map, int fd)
{
	if (is_map_line(line) != 0)
	{
		if (map_start_line == 0)
			*map_start_line = current_line - 1;
	}
	else
	{
		free(line);
		close (fd);
		free_map(map);
		printf("Error: invalid map line\n");
		clear_gnl();
		exit(1);
	}
}

void	parse_file(char **av, int fd, t_map_data *map)
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
				if (map_start_line == 0)
					map_start_line = current_line - 1;
			}
			else
			{
				free(line);
				close (fd);
				free_map(map);
				printf("Error: invalid map line\n");
				clear_gnl();
				exit(1);
			}
		}
		else
		{
			if (is_map_line(line))
			{
				close(fd);
				printf("Error: Invalid configuration line\n");
			}
			else
			{
				parse_config_line(line, map, fd);
				if (map->north_txtr && map->south_txtr && map->west_txtr
					&& map->east_txtr && map->floor_color && map->ceiling_color)
					config_done = 1;
			}
		}
		free(line);
	}
	close(fd);
	if (!current_line)
	{
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
