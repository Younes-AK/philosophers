/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:07:54 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/04 11:05:06 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	init_sem(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/write_sem");
	sem_unlink("/meals_sem");
	data->forks = sem_open("/forks", O_CREAT, S_IRWXU, data->nbr_philos);
	if (data->forks == SEM_FAILED)
		return (ft_error("Error\nsem_open failed"), false);
	data->write_sem = sem_open("/write_sem", O_CREAT, S_IRWXU, 1);
	if (data->write_sem == SEM_FAILED)
	{
		sem_close(data->forks);
		return (ft_error("Error\nsem_open failed"), false);
	}
	data->meals_sem = sem_open("/meals_sem", O_CREAT, S_IRWXU, 1);
	if (data->meals_sem == SEM_FAILED)
	{
		sem_close(data->forks);
		sem_close(data->write_sem);
		return (ft_error("Error\nsem_open failed"), false);
	}
	return (true);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		data->philos[i].philo_id = i;
		data->philos[i].meals_count = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].data = data;
		i++;
	}
}

int	data_init(t_data *data, char **av)
{
	data->nbr_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	data->is_died = false;
	if (av[5])
	{
		data->nbr_meals_to_eat = ft_atol(av[5]);
		if (ft_atol(av[5]) == 0)
			return (1);
	}
	else
		data->nbr_meals_to_eat = -1;
	if (!init_sem(data))
		return (1);
	init_philos(data);
	return (0);
}
