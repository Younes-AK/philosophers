/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:46:38 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/03 18:14:01 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_all_full(t_philo *philo)
{
	int	i;
	int	eat_count;

	i = 0;
	eat_count = 0;
	if (philo[0].nbr_times_to_eat == -1)
		return (false);
	while (i < philo[0].nbr_of_philos)
	{
		pthread_mutex_lock(philo->meal_mutex);
		if (philo[i].nbr_meals_eaten >= philo[i].nbr_times_to_eat)
			eat_count++;
		pthread_mutex_unlock(philo->meal_mutex);
		i++;
	}
	if (eat_count == philo[0].nbr_of_philos)
	{
		pthread_mutex_lock(philo[0].dead_mutex);
		*philo->is_dead = true;
		pthread_mutex_unlock(philo[0].dead_mutex);
		return (true);
	}
	return (false);
}

bool	ft_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_mutex);
	if (get_current_time() - philo->last_meal_time >= time_to_die
		&& philo->is_eating_now == false)
		return (pthread_mutex_unlock(philo->meal_mutex), true);
	pthread_mutex_unlock(philo->meal_mutex);
	return (false);
}

bool	is_philo_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].nbr_of_philos)
	{
		if (ft_dead(&philo[i], philo[i].time_to_die))
		{
			ft_write_handle(&philo[i], philo[i].philo_id, "died");
			pthread_mutex_lock(philo[0].dead_mutex);
			*philo->is_dead = true;
			pthread_mutex_unlock(philo[0].dead_mutex);
			return (true);
		}
		i++;
	}
	return (false);
}

void	*monitor(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (true)
	{
		if (is_philo_dead(philo) == true || is_all_full(philo) == true)
			break ;
	}
	return (data);
}
