/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 22:52:55 by mariel            #+#    #+#             */
/*   Updated: 2025/04/27 18:44:19 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_config_line(char *str, t_map_data *map, int fd)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (!ft_strncmp(str + i, "NO ", 3) || !ft_strncmp(str + i, "SO ", 3))
		handle_texture(map, fd, str + i, i + 3);
	else if (!ft_strncmp(str + i, "WE ", 3) || !ft_strncmp(str + i, "EA ", 3))
		handle_texture(map, fd, str + i, i + 3);
	else if (!ft_strncmp(str + i, "F ", 2) || !ft_strncmp(str + i, "C ", 2))
		parse_floor_ceiling(i, str, map, fd);
	else
	{
		free(str);
		handle_config_error(fd, map,
			"Error\nUnknown configuration directive\n");
	}
}

void	process_line(char *line, t_map_data *map, int fd, t_parse_state *state)
{
	state->current_line++;
	if (is_empty_line(line))
	{
		free(line);
		return ;
	}
	if (state->config_done)
	{
		if (!handle_map_line(line, state->current_line, &state->map_start_line))
			handle_map_error(line, fd, map, "Error\nInvalid map line\n");
	}
	else
		handle_config_line(line, map, fd, &state->config_done);
	free(line);
}

void	parse_file(char **av, int fd, t_map_data *map)
{
	char			*line;
	t_parse_state	state;

	state.config_done = 0;
	state.map_start_line = 0;
	state.current_line = 0;
	init_map(map);
	line = get_next_line(fd);
	while (line)
	{
		process_line(line, map, fd, &state);
		line = get_next_line(fd);
	}
	close(fd);
	check_empty_file(state.current_line, map);
	load_and_check_map(av, map, state.map_start_line);
}
