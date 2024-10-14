/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:01:48 by mabrigo           #+#    #+#             */
/*   Updated: 2024/10/06 20:37:07 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data)
{
	int	i;

	data->end_simulation = 0;
	data->start_simulation = get_time();
	data->last_meal_time = malloc(sizeof(long long) * data->philo_nbr);
	if (!data->last_meal_time)
		return (printf("Malloc error in last_meal_time\n"));
	i = -1;
	while (++i < data->philo_nbr)
		data->last_meal_time[i] = data->start_simulation;
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philo_nbr)
		return (printf("Malloc error in philos"));
	i = 0;
	while (i < data->philo_nbr)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].last_meal_time = data->start_simulation;
		data->philos[i].meals_counter = 0;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->philo_nbr;
		i++;
	}
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nbr);
	if (!data->forks)
		return (printf("Malloc error in forks\n"));
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (printf("Error: Fork initialization failed\n"));
		i++;
	}
	if (pthread_mutex_init(&data->write_mutex, NULL)
		|| pthread_mutex_init(&data->meal_mutex, NULL)
		|| pthread_mutex_init(&data->end_mutex, NULL))
		return (printf("Error: Mutex initialization failed\n"));
	return (0);
}
