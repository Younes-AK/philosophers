/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:20:48 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/04 11:25:28 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	data = philo->data;
	sem_wait(data->forks);
	write_handle(data, philo->philo_id, "has taken a fork");
	sem_wait(data->forks);
	write_handle(data, philo->philo_id, "has taken a fork");
	sem_wait(data->meals_sem);
	write_handle(data, philo->philo_id, "is eating");
	philo->last_meal_time = get_curr_time();
	sem_post(data->meals_sem);
	ft_usleep(data->time_to_eat, data);
	philo->meals_count++;
	sem_post(data->forks);
	sem_post(data->forks);
}

void	*monitoring(void *data_routine)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)data_routine;
	data = philo->data;
	while (true)
	{
		sem_wait(data->meals_sem);
		if (gap(get_curr_time(), philo->last_meal_time) >= data->time_to_die)
		{
			data->is_died = true;
			sem_wait(data->write_sem);
			write_handle1(data, philo->philo_id, "died");
			exit(1);
		}
		sem_post(data->meals_sem);
		if (data->is_died)
			break ;
		usleep(1000);
		if (philo->meals_count >= data->nbr_meals_to_eat
			&& data->nbr_meals_to_eat != -1)
			break ;
	}
	return (NULL);
}

void	child_process(void *philo_data)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_data;
	data = philo->data;
	philo->last_meal_time = get_curr_time();
	pthread_create(&philo->observe, NULL, monitoring, philo_data);
	if (philo->philo_id % 2)
		usleep (15000);
	while (!data->is_died)
	{
		eating(philo);
		if (philo->meals_count >= data->nbr_meals_to_eat
			&& data->nbr_meals_to_eat != -1)
			break ;
		write_handle(data, philo->philo_id, "is sleeping");
		ft_usleep(data->time_to_eat, data);
		write_handle(data, philo->philo_id, "is thinking");
	}
	pthread_join(philo->observe, NULL);
	if (data->is_died)
		exit(1);
	exit(0);
}

bool	create_childs(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = data->philos;
	data->start_simulation = get_curr_time();
	while (i < data->nbr_philos)
	{
		philo[i].pid = fork();
		if (philo[i].pid < 0)
		{
			ft_error("Error\nFork() failled");
			return (false);
		}
		if (philo[i].pid == 0)
			child_process(&(philo[i]));
		usleep (100);
		i++;
	}
	return (true);
}

int	dinner_routine(t_data *data)
{
	if (!create_childs(data))
		return (1);
	end_simulation(data);
	sem_exit(data);
	return (0);
}
