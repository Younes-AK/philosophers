/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:24:49 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/04 08:32:43 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->nbr_of_philos)
	{
		if (pthread_mutex_init(&data->fork_mutex[i++], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->fork_mutex[i]);
			pthread_mutex_destroy(&data->write_mutex);
			pthread_mutex_destroy(&data->dead_mutex);
			pthread_mutex_destroy(&data->meal_mutex);
			free(philos);
			free(data->fork_mutex);
			return (1);
		}
	}
	return (0);
}

void	ft_destroy_mutex(t_data *data, int nbr_of_philos)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	while (i < nbr_of_philos)
	{
		pthread_mutex_destroy(&data->fork_mutex[i]);
		i++;
	}
	free(data->philos);
	free(data->fork_mutex);
}

bool	check_read(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_mutex);
	if (*philo->is_dead)
		return (pthread_mutex_unlock(philo->dead_mutex), true);
	pthread_mutex_unlock(philo->dead_mutex);
	return (false);
}

int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds && !check_read(philo))
		usleep(500);
	return (0);
}

size_t	get_current_time(void)
{
	int				state;
	struct timeval	time;

	state = gettimeofday(&time, NULL);
	if (state == -1)
		ft_error("Error: gettimeofday failed\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
