/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:26:06 by mabrigo           #+#    #+#             */
/*   Updated: 2024/10/07 11:41:33 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo, t_data *data, int first_fork, int second_fork)
{
	long long	current_time;

	pthread_mutex_lock(&data->forks[first_fork]);
	if (try(data, philo))
	{
		pthread_mutex_unlock(&data->forks[first_fork]);
		return ;
	}
	write_status(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&data->forks[second_fork]);
	write_status(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&data->meal_mutex);
	current_time = get_time();
	philo->last_meal_time = current_time;
	data->last_meal_time[philo->id - 1] = current_time;
	philo->meals_counter++;
	pthread_mutex_unlock(&data->meal_mutex);
	write_status(data, philo->id, "is eating");
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->forks[second_fork]);
	pthread_mutex_unlock(&data->forks[first_fork]);
}

void	eat(t_philo *philo)
{
	t_data	*data;
	int		first_fork;
	int		second_fork;

	data = philo->data;
	if (data->philo_nbr == 1)
	{
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		write_status(data, philo->id, "has taken a fork");
		usleep(data->time_to_die * 1000);
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		write_status(data, philo->id, "died");
		return ;
	}
	first_fork = philo->left_fork;
	second_fork = philo->right_fork;
	if (philo->id % 2 == 0)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	eating(philo, data, first_fork, second_fork);
}

void	think(t_philo *philo, int initial)
{
	long long	time_to_think;

	pthread_mutex_lock(&philo->data->end_mutex);
	if (philo->data->end_simulation)
	{
		pthread_mutex_unlock(&philo->data->end_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->end_mutex);
	if (initial && philo->id % 2)
	{
		time_to_think = philo->data->time_to_eat / 2;
		write_status(philo->data, philo->id, "is thinking");
	}
	else
		write_status(philo->data, philo->id, "is thinking");
}

void	ft_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	write_status(data, philo->id, "is sleeping");
	usleep(data->time_to_sleep * 1000);
}

int	death(t_data *data, t_philo *philo, int died, long long current)
{
	pthread_mutex_lock(&data->end_mutex);
	if (!data->end_simulation)
	{
		data->end_simulation = 1;
		died = 1;
		pthread_mutex_lock(&data->write_mutex);
		printf("%lld %d died\n", current - data->start_simulation, philo->id);
		pthread_mutex_unlock(&data->write_mutex);
	}
	pthread_mutex_unlock(&data->end_mutex);
	return (died);
}
