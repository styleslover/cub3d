/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:10:52 by mabrigo           #+#    #+#             */
/*   Updated: 2024/10/06 20:36:10 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_data *data, t_philo *philo)
{
	long long	current;
	long long	last_meal;

	current = get_time();
	pthread_mutex_lock(&data->meal_mutex);
	last_meal = data->last_meal_time[philo->id - 1];
	pthread_mutex_unlock(&data->meal_mutex);
	if (current - last_meal > data->time_to_die)
		return (death(data, philo, 1, current));
	return (0);
}

int	try(t_data *data, t_philo *philo)
{
	int	i;

	(void)philo;
	i = 0;
	while (i < data->philo_nbr)
	{
		if (check_death(data, &data->philos[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

static int	check_all_done(t_data *data, int all_done)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		if (data->philos[i].meals_counter < data->min_meals)
		{
			all_done = 0;
			return (all_done);
		}
		i++;
	}
	if (all_done)
	{
		data->end_simulation = 1;
		pthread_mutex_unlock(&data->end_mutex);
	}
	return (all_done);
}

int	is_all_done(t_data *data)
{
	int	all_done;

	all_done = 1;
	pthread_mutex_lock(&data->end_mutex);
	if (data->end_simulation)
	{
		pthread_mutex_unlock(&data->end_mutex);
		return (-1);
	}
	if (data->min_meals != -1)
	{
		check_all_done(data, all_done);
	}
	pthread_mutex_unlock(&data->end_mutex);
	return (1);
}
