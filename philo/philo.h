/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:39:32 by mabrigo           #+#    #+#             */
/*   Updated: 2024/10/06 20:33:53 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				right_fork;
	int				left_fork;
	int				meals_counter;
	long long		last_meal_time;
	struct s_data	*data;
	pthread_t		thread;
}	t_philo;

typedef struct s_data
{
	int				philo_nbr;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				min_meals;
	int				end_simulation;
	long long		start_simulation;
	long long		*last_meal_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	end_mutex;
}	t_data;

//init.c
int			init_data(t_data *data);
int			init_philos(t_data *data);
int			init_mutex(t_data *data);

//moitoring.c
int			check_death(t_data *data, t_philo *philo);
int			try(t_data *data, t_philo *philo);
int			is_all_done(t_data *data);

//parse.c - full
int			parse_input(t_data *data, char **av);

//utils.c
long long	get_time(void);
void		write_status(t_data *data, int id, char *status);
void		smart_sleep(t_data *data, t_philo *philo, long long time);
void		clean(t_data data);

//philo_actions.c
void		eat(t_philo *philo);
void		eating(t_philo *philo, t_data *data,
				int first_fork, int second_fork);
void		think(t_philo *philo, int initial);
void		ft_sleep(t_philo *philo);
int			death(t_data *data, t_philo *philo, int died, long long current);

#endif