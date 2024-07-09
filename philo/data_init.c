/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:21:27 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/04 08:57:33 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_is_dead(t_philo *philo)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(philo->dead_mutex);
	if (*philo->is_dead == true)
		ret = *philo->is_dead;
	pthread_mutex_unlock(philo->dead_mutex);
	return (ret);
}

void	*dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->philo_id % 2 == 0)
		ft_usleep(philo->time_to_eat, philo);
	while (!check_is_dead(philo))
	{
		eating(philo);
		ft_write_handle(philo, philo->philo_id, "is sleeping");
		ft_usleep(philo->time_to_sleep, philo);
		ft_write_handle(philo, philo->philo_id, "is thinking");
	}
	return (data);
}

void	create_join_threads(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_create(&data->observer, NULL, &monitor, data->philos) != 0)
		ft_destroy_mutex(data, data->philos->nbr_of_philos);
	while (i < data->philos[0].nbr_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &dinner,
				&data->philos[i]) != 0)
			ft_destroy_mutex(data, data->philos->nbr_of_philos);
		i++;
	}
	if (pthread_join(data->observer, NULL) != 0)
		ft_destroy_mutex(data, data->philos->nbr_of_philos);
	i = 0;
	while (i < data->philos->nbr_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			ft_destroy_mutex(data, data->philos->nbr_of_philos);
		i++;
	}
}

void	philos_init(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos[0].nbr_of_philos)
	{
		philos[i].philo_id = i + 1;
		philos[i].is_eating_now = false;
		philos[i].nbr_meals_eaten = 0;
		philos[i].last_meal_time = get_current_time();
		philos[i].start_simulation = get_current_time();
		philos[i].write_mutex = &data->write_mutex;
		philos[i].dead_mutex = &data->dead_mutex;
		philos[i].meal_mutex = &data->meal_mutex;
		philos[i].is_dead = &data->dead;
		philos[i].r_fork = &data->fork_mutex[i];
		if (i == 0)
			philos[i].l_fork = &data->fork_mutex[philos[i].nbr_of_philos - 1];
		else
			philos[i].l_fork = &data->fork_mutex[i - 1];
		i++;
	}
}

int	data_init(t_data *data, t_philo *philos)
{
	int	nbr;

	data->dead = false;
	data->philos = philos;
	nbr = philos[0].nbr_of_philos;
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
		return (free(philos), free(data->fork_mutex), 1);
	if (pthread_mutex_init(&data->dead_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->write_mutex);
		return (free(philos), free(data->fork_mutex), 1);
	}
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->write_mutex);
		pthread_mutex_destroy(&data->dead_mutex);
		return (free(philos), free(data->fork_mutex), 1);
	}
	if (init_forks(data, philos) == 1)
		return (1);
	philos_init(philos, data);
	create_join_threads(data);
	ft_destroy_mutex(data, philos->nbr_of_philos);
	return (0);
}
