/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsinf_fc_rgb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 00:05:02 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/25 00:05:46 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_digit_and_spaces(char *str, int *i,
	int *digit_found, int *in_number)
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
	int	i;
	int	digit_found;
	int	in_number;

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

int	rgb_char_to_int(int *rgb_values, char **input)
{
	int		i;
	char	*trimmed;

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

int	*parse_rgb_values(char *str)
{
	char	**splitted;
	int		*rgb_values;

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

