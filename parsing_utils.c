/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 23:58:46 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/27 20:19:47 by mabrigo          ###   ########.fr       */
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

int	is_valid_config_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	return (ft_strncmp(str + i, "NO ", 3) == 0
		|| ft_strncmp(str + i, "SO ", 3) == 0
		|| ft_strncmp(str + i, "WE ", 3) == 0
		|| ft_strncmp(str + i, "EA ", 3) == 0
		|| ft_strncmp(str + i, "NO\t", 3) == 0
		|| ft_strncmp(str + i, "SO\t", 3) == 0
		|| ft_strncmp(str + i, "WE\t", 3) == 0
		|| ft_strncmp(str + i, "EA\t", 3) == 0
		|| ft_strncmp(str + i, "F ", 2) == 0
		|| ft_strncmp(str + i, "C ", 2) == 0
		|| ft_strncmp(&str[i], "F\t", 2) == 0
		|| ft_strncmp(&str[i], "C\t", 2) == 0);
}

void	check_empty_file(int current_line, t_map_data *map)
{
	if (!current_line)
	{
		free_map(map);
		printf("Error\nEmpty file\n");
		exit(1);
	}
}

int	skip_spaces_check_sign(char *str, int *i)
{
	while (str[*i] == ' ' || (str[*i] >= '\t' && str[*i] <= '\r'))
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (!ft_isdigit(str[*i + 1]))
		{
			return (0);
		}
		(*i)++;
	}
	return (1);
}
