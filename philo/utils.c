/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:05:16 by mabrigo           #+#    #+#             */
/*   Updated: 2024/10/07 11:36:35 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	write_status(t_data *data, int id, char *status)
{
	pthread_mutex_lock(&data->end_mutex);
	if (!data->end_simulation)
	{
		pthread_mutex_lock(&data->write_mutex);
		printf("%lld %d %s\n", get_time() - data->start_simulation, id, status);
		pthread_mutex_unlock(&data->write_mutex);
	}
	pthread_mutex_unlock(&data->end_mutex);
}

void	smart_sleep(t_data *data, t_philo *philo, long long time)
{
	long long	start;
	long long	elapsed;

	start = get_time();
	while (1)
	{
		pthread_mutex_lock(&data->end_mutex);
		if (data->end_simulation)
		{
			pthread_mutex_unlock(&data->end_mutex);
			return ;
		}
		pthread_mutex_unlock(&data->end_mutex);
		if (check_death(data, philo))
			return ;
		elapsed = get_time() - start;
		if (elapsed >= time)
			return ;
		usleep(100);
	}
}

void	clean(t_data data)
{
	int	i;

	i = 0;
	while (i < data.philo_nbr)
		pthread_mutex_destroy(&data.forks[i++]);
	pthread_mutex_destroy(&data.write_mutex);
	pthread_mutex_destroy(&data.meal_mutex);
	pthread_mutex_destroy(&data.end_mutex);
	free(data.philos);
	free(data.forks);
	free(data.last_meal_time);
}
