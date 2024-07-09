/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:49:36 by yakazdao          #+#    #+#             */
/*   Updated: 2024/06/24 14:26:47 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (-1);
}

void	ft_write_handle(t_philo *philo, int philo_id, char *philo_state)
{
	size_t	time;

	pthread_mutex_lock(philo->write_mutex);
	time = get_current_time() - philo->start_simulation;
	if (!check_is_dead(philo))
		printf("%zu %d %s\n", time, philo_id, philo_state);
	pthread_mutex_unlock(philo->write_mutex);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_write_handle(philo, philo->philo_id, "has taken a fork");
	if (philo->nbr_of_philos == 1)
	{
		ft_usleep(philo->time_to_die, philo);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	ft_write_handle(philo, philo->philo_id, "has taken a fork");
	philo->is_eating_now = true;
	ft_write_handle(philo, philo->philo_id, "is eating");
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_meal_time = get_current_time();
	philo->nbr_meals_eaten++;
	pthread_mutex_unlock(philo->meal_mutex);
	ft_usleep(philo->time_to_eat, philo);
	philo->is_eating_now = false;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
