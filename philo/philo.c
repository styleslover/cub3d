/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:39:19 by mabrigo           #+#    #+#             */
/*   Updated: 2024/10/07 11:42:17 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*cycle(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	think(philo, 1);
	if (philo->id % 2 == 0)
	{
		think(philo, 0);
	}
	while (1)
	{
		if (try(data, philo) || is_all_done(data) == -1)
			break ;
		eat(philo);
		if (data->philo_nbr == 1)
			break ;
		ft_sleep(philo);
		think(philo, 0);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (ac != 5 && ac != 6)
		return (printf("Invalid input!\nInput example: \
		./philo 5 800 200 200 [2]\n"));
	if (parse_input(&data, av) == 0 && (init_data(&data)
			|| init_mutex(&data) || init_philos(&data)))
		return (1);
	i = -1;
	while (++i < data.philo_nbr)
	{
		if (pthread_create(&data.philos[i].thread, NULL,
				cycle, &data.philos[i]))
			return (printf("Error: Thread creation error\n"));
	}
	i = -1;
	while (++i < data.philo_nbr)
	{
		if (pthread_join(data.philos[i].thread, NULL))
			return (printf("Error: Joining thread failed\n"));
	}
	clean(data);
	return (0);
}
