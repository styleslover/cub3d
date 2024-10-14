/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:56:35 by mabrigo           #+#    #+#             */
/*   Updated: 2024/10/07 11:13:33 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(char c)
{
	char	*nbr;

	nbr = "0123456789";
	while (*nbr)
		if (c == *nbr++)
			return (1);
	return (0);
}

static int	is_int_number(char *s)
{
	while (*s)
	{
		if (*s == '+' || *s == '-')
			s++;
		if (!is_digit(*s))
		{
			printf("Please type only integer number");
			exit(0);
		}
		s++;
	}
	return (1);
}

static long	ft_atol(char *s)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (!*s)
		printf("Please type valid number");
	if (is_int_number(s))
	{
		if (s[i] == '-' || s[i] == '+')
		{
			if (s[i] == '-')
				sign = -1;
			i++;
		}
	}
	while (s[i] >= '0' && s[i] <= '9')
		result = result * 10 + (s[i++] - '0');
	return (result * sign);
}

static int	is_valid(long nbr)
{
	if (nbr > INT_MAX || nbr < INT_MIN)
		exit (printf("INVALID\n"));
	if (nbr < 0)
		exit (printf("INVALID\n"));
	else
		return (1);
}

int	parse_input(t_data *data, char **av)
{
	int	i;

	i = 1;
	while (i <= 4)
	{
		if (is_valid(ft_atol(av[i])))
			i++;
		else
			return (printf("Invalid input, \
			please choose positive numbers only\n"));
	}
	data->philo_nbr = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->min_meals = ft_atol(av[5]);
	else
		data->min_meals = -1;
	return (0);
}
